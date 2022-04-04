#include "OsmDataProvider.h"

#include <QDebug>
#include <QFileInfo>
#include <chrono>

namespace ibh {
bool OsmDataProvider::open(const QString& path)
{
    qInfo() << "Opening spatial database" << path;
    const auto file = QFileInfo(path);
    if (!file.exists()) {
        qWarning() << "Cannot open file '" << path << "', because it does not exist";
        return {};
    }

    GDALAllRegister();

    m_dataset = static_cast<GDALDataset*>(GDALOpenEx(path.toStdString().c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL));
    if (!m_dataset) {
        qWarning() << "Opening file '" << path << "' failed";
        return {};
    }

    return true;
}

bool OsmDataProvider::close()
{
    qInfo() << "Closing spatial database";
    GDALClose(m_dataset);
    m_dataset = nullptr;
    return true;
}

void OsmDataProvider::searchStreet(const int cityId, const QString& streetName)
{
    qInfo() << QString("Search streets with name '%1' in city with ID '%2'").arg(streetName).arg(cityId);

    if (streetName.isEmpty()) {
        qWarning() << "Cannot search streets without a given name";
        return;
    }

    if (cityId <= 0) {
        qWarning() << "Cannot search streets without a given valid city ID";
        return;
    }

    if (!m_dataset) {
        qWarning() << "Cannot search street, because dataset is not set";
        return;
    }

    // search boundary polygon around given city
    const auto cityBoundaryTable = "ln_boundary";
    OGRLayer* poLayer = m_dataset->GetLayerByName(cityBoundaryTable);
    if (!poLayer) {
        qCritical() << "Failed to get layer for table " << cityBoundaryTable;
        assert(0);
        return;
    }
    poLayer->ResetReading(); // ensure starting at beginning of layer
    auto poFeature = poLayer->GetFeature(cityId);
    if (!poFeature) {
        qDebug() << "No city found with ID " << cityId;
        return;
    }
    const auto foundBoundary = poFeature->GetGeometryRef();

    // search streets within boundary bounding box
    const auto highwayTable = "ln_highway";
    poLayer = m_dataset->GetLayerByName(highwayTable);
    const auto streetNameFilter = QString("name LIKE '%1%'").arg(streetName);
    poLayer->SetAttributeFilter(streetNameFilter.toStdString().c_str());
    OGREnvelope envelope;
    foundBoundary->getEnvelope(&envelope);
    poLayer->SetSpatialFilterRect(envelope.MinX, envelope.MinY, envelope.MaxX, envelope.MaxY);
    OGRFeature::DestroyFeature(poFeature);
    poFeature = nullptr;

    auto start = std::chrono::steady_clock::now();
    while ((poFeature = poLayer->GetNextFeature())) {
        auto end = std::chrono::steady_clock::now();
        qInfo() << "Time needed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms";

        start = std::chrono::steady_clock::now();
        const auto id = poFeature->GetFID();
        const auto nameIndex = poFeature->GetFieldIndex("name");
        const auto name = poFeature->GetFieldAsString(nameIndex);

        qInfo() << "Found street: ID: " << id << "; name:" << name;
    }

    // reset filter for future queries
    poLayer->SetAttributeFilter("");
}
}
