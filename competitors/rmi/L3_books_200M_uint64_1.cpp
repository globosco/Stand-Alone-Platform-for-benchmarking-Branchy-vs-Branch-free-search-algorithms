#include "L3_books_200M_uint64_1.h"
#include "L3_books_200M_uint64_1_data.h"
#include <math.h>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>
namespace L3_books_200M_uint64_1 {
bool load(char const* dataPath) {
  {
    std::ifstream infile(std::filesystem::path(dataPath) / "L3_books_200M_uint64_1_L1_PARAMETERS", std::ios::in | std::ios::binary);
    if (!infile.good()) return false;
    L1_PARAMETERS = (char*) malloc(6291456);
    if (L1_PARAMETERS == NULL) return false;
    infile.read((char*)L1_PARAMETERS, 6291456);
    if (!infile.good()) return false;
  }
  return true;
}
void cleanup() {
    free(L1_PARAMETERS);
}

inline uint64_t radix(uint64_t prefix_length, uint64_t bits, uint64_t inp) {
    return (inp << prefix_length) >> (64 - bits);
}

inline double linear(double alpha, double beta, double inp) {
    return std::fma(beta, inp, alpha);
}

inline size_t FCLAMP(double inp, double bound) {
  if (inp < 0.0) return 0;
  return (inp > bound ? bound : (size_t)inp);
}

uint64_t lookup(uint64_t key, size_t* err) {
  uint64_t ipred;
  double fpred;
  size_t modelIndex;
  ipred = radix(L0_PARAMETER0, L0_PARAMETER1, (uint64_t)key);
  modelIndex = ipred;
  fpred = linear(*((double*) (L1_PARAMETERS + (modelIndex * 24) + 0)), *((double*) (L1_PARAMETERS + (modelIndex * 24) + 8)), (double)key);
  *err = *((uint64_t*) (L1_PARAMETERS + (modelIndex * 24) + 16));

  return FCLAMP(fpred, 750000.0 - 1.0);
}
} // namespace
