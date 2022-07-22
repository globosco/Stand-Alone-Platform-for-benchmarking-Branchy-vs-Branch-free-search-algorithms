#include <cstddef>
#include <cstdint>
namespace L4_osm_cellids_200M_uint64_4 {
bool load(char const* dataPath);
void cleanup();
const size_t RMI_SIZE = 12582944;
const uint64_t BUILD_TIME_NS = 0;
const char NAME[] = "L4_osm_cellids_200M_uint64_4";
uint64_t lookup(uint64_t key, size_t* err);
}
