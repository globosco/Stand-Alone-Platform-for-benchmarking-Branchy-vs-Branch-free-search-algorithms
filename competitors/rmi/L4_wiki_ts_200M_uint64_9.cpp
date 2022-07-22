#include "L4_wiki_ts_200M_uint64_9.h"
#include "L4_wiki_ts_200M_uint64_9_data.h"
#include <math.h>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>
namespace L4_wiki_ts_200M_uint64_9 {
bool load(char const* dataPath) {
  {
    std::ifstream infile(std::filesystem::path(dataPath) / "L4_wiki_ts_200M_uint64_9_L1_PARAMETERS", std::ios::in | std::ios::binary);
    if (!infile.good()) return false;
    L1_PARAMETERS = (char*) malloc(3072);
    if (L1_PARAMETERS == NULL) return false;
    infile.read((char*)L1_PARAMETERS, 3072);
    if (!infile.good()) return false;
  }
  return true;
}
void cleanup() {
    free(L1_PARAMETERS);
}

inline double linear(double alpha, double beta, double inp) {
    return std::fma(beta, inp, alpha);
}

inline size_t FCLAMP(double inp, double bound) {
  if (inp < 0.0) return 0;
  return (inp > bound ? bound : (size_t)inp);
}

uint64_t lookup(uint64_t key, size_t* err) {
  size_t modelIndex;
  double fpred;
  fpred = linear(L0_PARAMETER0, L0_PARAMETER1, (double)key);
  modelIndex = FCLAMP(fpred, 128.0 - 1.0);
  fpred = linear(*((double*) (L1_PARAMETERS + (modelIndex * 24) + 0)), *((double*) (L1_PARAMETERS + (modelIndex * 24) + 8)), (double)key);
  *err = *((uint64_t*) (L1_PARAMETERS + (modelIndex * 24) + 16));

  return FCLAMP(fpred, 200000000.0 - 1.0);
}
} // namespace
