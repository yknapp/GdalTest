#pragma once

#include "ogrsf_frmts.h"

namespace ibh {
class OsmDataProvider {
public:
    bool open(const std::string& path);
    bool close();
    void searchStreet(const int cityId, const std::string& streetName);

private:
    std::string m_filePath;
    GDALDataset* m_dataset;
};
}
