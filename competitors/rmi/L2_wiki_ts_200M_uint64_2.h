#include <cstddef>
#include <cstdint>
namespace L2_wiki_ts_200M_uint64_2 {
bool load(char const* dataPath);
void cleanup();
const size_t RMI_SIZE = 786464;
const uint64_t BUILD_TIME_NS = 0;
const char NAME[] = "L2_wiki_ts_200M_uint64_2";
uint64_t lookup(uint64_t key, size_t* err);
}
