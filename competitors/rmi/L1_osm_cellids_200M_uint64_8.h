#include <cstddef>
#include <cstdint>
namespace L1_osm_cellids_200M_uint64_8 {
bool load(char const* dataPath);
void cleanup();
const size_t RMI_SIZE = 6160;
const uint64_t BUILD_TIME_NS = 0;
const char NAME[] = "L1_osm_cellids_200M_uint64_8";
uint64_t lookup(uint64_t key, size_t* err);
}
