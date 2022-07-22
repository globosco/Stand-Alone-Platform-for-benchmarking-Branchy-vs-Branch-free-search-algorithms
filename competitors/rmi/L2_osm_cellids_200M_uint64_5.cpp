#include "L2_osm_cellids_200M_uint64_5.h"
#include "L2_osm_cellids_200M_uint64_5_data.h"
#include <math.h>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>
namespace L2_osm_cellids_200M_uint64_5 {
bool load(char const* dataPath) {
  {
    std::ifstream infile(std::filesystem::path(dataPath) / "L2_osm_cellids_200M_uint64_5_L0_PARAMETERS", std::ios::in | std::ios::binary);
    if (!infile.good()) return false;
    L0_PARAMETERS = (uint32_t*) malloc(1048576);
    if (L0_PARAMETERS == NULL) return false;
    infile.read((char*)L0_PARAMETERS, 1048576);
    if (!infile.good()) return false;
  }
  {
    std::ifstream infile(std::filesystem::path(dataPath) / "L2_osm_cellids_200M_uint64_5_L1_PARAMETERS", std::ios::in | std::ios::binary);
    if (!infile.good()) return false;
    L1_PARAMETERS = (char*) malloc(786432);
    if (L1_PARAMETERS == NULL) return false;
    infile.read((char*)L1_PARAMETERS, 786432);
    if (!infile.good()) return false;
  }
  return true;
}
void cleanup() {
    free(L0_PARAMETERS);
    free(L1_PARAMETERS);
}

inline double linear(double alpha, double beta, double inp) {
    return std::fma(beta, inp, alpha);
}

inline uint64_t radix_table(const uint32_t* table, const uint64_t inp) {
    return table[((inp << 0) >> 0) >> 46];
}

inline size_t FCLAMP(double inp, double bound) {
  if (inp < 0.0) return 0;
  return (inp > bound ? bound : (size_t)inp);
}

uint64_t lookup(uint64_t key, size_t* err) {
  uint64_t ipred;
  size_t modelIndex;
  double fpred;
  ipred = radix_table(L0_PARAMETERS, (uint64_t)key);
  modelIndex = ipred;
  fpred = linear(*((double*) (L1_PARAMETERS + (modelIndex * 24) + 0)), *((double*) (L1_PARAMETERS + (modelIndex * 24) + 8)), (double)key);
  *err = *((uint64_t*) (L1_PARAMETERS + (modelIndex * 24) + 16));

  return FCLAMP(fpred, 31500.0 - 1.0);
}
} // namespace
