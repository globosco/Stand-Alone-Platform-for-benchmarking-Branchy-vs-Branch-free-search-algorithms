#include <cstddef>
#include <cstdint>
namespace L3_books_200M_uint32_2 {
bool load(char const* dataPath);
void cleanup();
const size_t RMI_SIZE = 25165840;
const uint64_t BUILD_TIME_NS = 0;
const char NAME[] = "L3_books_200M_uint32_2";
uint64_t lookup(uint64_t key, size_t* err);
}
