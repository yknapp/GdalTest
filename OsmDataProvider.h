#pragma once

#include "ogrsf_frmts.h"

#include <QString>

namespace ibh {
class OsmDataProvider {
public:
    bool open(const QString& path);
    bool close();
    void searchStreet(const int cityId, const QString& streetName);

private:
    QString m_filePath;
    GDALDataset* m_dataset;
};
}
