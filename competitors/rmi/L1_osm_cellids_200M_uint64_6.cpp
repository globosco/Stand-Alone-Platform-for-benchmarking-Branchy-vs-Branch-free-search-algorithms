#include "L1_osm_cellids_200M_uint64_6.h"
#include "L1_osm_cellids_200M_uint64_6_data.h"
#include <math.h>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>
namespace L1_osm_cellids_200M_uint64_6 {
bool load(char const* dataPath) {
  {
    std::ifstream infile(std::filesystem::path(dataPath) / "L1_osm_cellids_200M_uint64_6_L1_PARAMETERS", std::ios::in | std::ios::binary);
    if (!infile.good()) return false;
    L1_PARAMETERS = (char*) malloc(40960);
    if (L1_PARAMETERS == NULL) return false;
    infile.read((char*)L1_PARAMETERS, 40960);
    if (!infile.good()) return false;
  }
  return true;
}
void cleanup() {
    free(L1_PARAMETERS);
}

inline double cubic(double a, double b, double c, double d, double x) {
    auto v1 = std::fma(a, x, b);
    auto v2 = std::fma(v1, x, c);
    auto v3 = std::fma(v2, x, d);
    return v3;
}

inline size_t FCLAMP(double inp, double bound) {
  if (inp < 0.0) return 0;
  return (inp > bound ? bound : (size_t)inp);
}

uint64_t lookup(uint64_t key, size_t* err) {
  double fpred;
  size_t modelIndex;
  fpred = cubic(L0_PARAMETER0, L0_PARAMETER1, L0_PARAMETER2, L0_PARAMETER3, (double)key);
  modelIndex = (uint64_t) fpred;
  fpred = cubic(*((double*) (L1_PARAMETERS + (modelIndex * 40) + 0)), *((double*) (L1_PARAMETERS + (modelIndex * 40) + 8)), *((double*) (L1_PARAMETERS + (modelIndex * 40) + 16)), *((double*) (L1_PARAMETERS + (modelIndex * 40) + 24)), (double)key);
  *err = *((uint64_t*) (L1_PARAMETERS + (modelIndex * 40) + 32));

  return FCLAMP(fpred, 3750.0 - 1.0);
}
} // namespace
