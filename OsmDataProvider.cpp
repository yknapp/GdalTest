#include "OsmDataProvider.h"

#include <chrono>
#include <iostream>

namespace ibh {
bool OsmDataProvider::open(const std::string& path)
{
    std::cout << "Opening spatial database\n";
    GDALAllRegister();

    m_dataset = static_cast<GDALDataset*>(GDALOpenEx(path.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL));
    if (!m_dataset) {
        std::cout << "Opening file '" << path << "' failed\n";
        return {};
    }

    return true;
}

bool OsmDataProvider::close()
{
    std::cout << "Closing spatial database\n";
    GDALClose(m_dataset);
    m_dataset = nullptr;
    return true;
}

void OsmDataProvider::searchStreet(const int cityId, const std::string& streetName)
{
    std::cout << "Search streets with name '" << streetName << "' in city with ID '" << cityId << "\n";

    if (streetName.empty()) {
        std::cout << "Cannot search streets without a given name\n";
        return;
    }

    if (cityId <= 0) {
        std::cout << "Cannot search streets without a given valid city ID\n";
        return;
    }

    if (!m_dataset) {
        std::cout << "Cannot search street, because dataset is not set\n";
        return;
    }

    // search boundary polygon around given city
    const auto cityBoundaryTable = "ln_boundary";
    OGRLayer* poLayer = m_dataset->GetLayerByName(cityBoundaryTable);
    if (!poLayer) {
        std::cout << "Failed to get layer for table " << cityBoundaryTable << "\n";
        return;
    }
    poLayer->ResetReading(); // ensure starting at beginning of layer
    auto poFeature = poLayer->GetFeature(cityId);
    if (!poFeature) {
        std::cout << "No city found with ID " << cityId << "\n";
        return;
    }
    const auto foundBoundary = poFeature->GetGeometryRef();

    // search streets within boundary bounding box
    const auto highwayTable = "ln_highway";
    poLayer = m_dataset->GetLayerByName(highwayTable);
    const auto streetNameFilter = "name LIKE '" + streetName + "%'";
    poLayer->SetAttributeFilter(streetNameFilter.c_str());
    OGREnvelope envelope;
    foundBoundary->getEnvelope(&envelope);
    poLayer->SetSpatialFilterRect(envelope.MinX, envelope.MinY, envelope.MaxX, envelope.MaxY);
    OGRFeature::DestroyFeature(poFeature);
    poFeature = nullptr;

    auto start = std::chrono::steady_clock::now();
    while ((poFeature = poLayer->GetNextFeature())) {
        auto end = std::chrono::steady_clock::now();
        std::cout << "Time needed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

        start = std::chrono::steady_clock::now();
        const auto id = poFeature->GetFID();
        const auto nameIndex = poFeature->GetFieldIndex("name");
        const auto name = poFeature->GetFieldAsString(nameIndex);

        std::cout << "Found street: ID: " << id << "; name:" << name << "\n";
    }

    // reset filter for future queries
    poLayer->SetAttributeFilter("");
}
}
