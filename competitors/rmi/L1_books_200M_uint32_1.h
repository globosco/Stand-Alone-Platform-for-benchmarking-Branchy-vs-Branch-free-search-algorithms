#include <cstddef>
#include <cstdint>
namespace L1_books_200M_uint32_1 {
bool load(char const* dataPath);
void cleanup();
const size_t RMI_SIZE = 393232;
const uint64_t BUILD_TIME_NS = 0;
const char NAME[] = "L1_books_200M_uint32_1";
uint64_t lookup(uint64_t key, size_t* err);
}
