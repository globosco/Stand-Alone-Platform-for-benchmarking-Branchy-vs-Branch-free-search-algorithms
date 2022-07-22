#include <cstddef>
#include <cstdint>
namespace L1_osm_cellids_200M_uint64_0 {
bool load(char const* dataPath);
void cleanup();
const size_t RMI_SIZE = 16875520;
const uint64_t BUILD_TIME_NS = 0;
const char NAME[] = "L1_osm_cellids_200M_uint64_0";
uint64_t lookup(uint64_t key, size_t* err);
}
