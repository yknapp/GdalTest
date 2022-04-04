#include <main.h>

int main(int argc, char* argv[])
{
    ibh::OsmDataProvider provider;
    // path to OSM database
    QString osmFilePath = "";
    provider.open(osmFilePath);

    auto start = std::chrono::steady_clock::now();
    provider.searchStreet(2783849, "Markt");
    auto end = std::chrono::steady_clock::now();
    std::cout << "searchStreet: Time needed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    provider.close();
    return 0;
}
