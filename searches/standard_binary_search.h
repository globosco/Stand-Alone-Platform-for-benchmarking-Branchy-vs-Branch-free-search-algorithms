#pragma once
#include "search.h"

template <typename KeyType>
class StandardBinarySearch : public Search<KeyType> {
 public:
  static uint64_t search( std::vector<Row<KeyType>>& data,
                   KeyType lookup_key,
                  size_t start, size_t end) {


        int lo = start;
        int hi = end;
        long m = 0;
        while (lo <= hi) {
            m = (lo + hi) / 2;
            __builtin_prefetch(&(data[lo + m / 2]), 0, 0);
            __builtin_prefetch(&(data[m + m / 2]), 0, 0);
            if (lookup_key < data[m].key) {
                hi = m-1;
            } else if (lookup_key > data[m].key) {
                lo = m+1;
            } else {
                return m;
            }
        }
        return hi;

  }
  static void createLayout( std::vector<Row<KeyType>>& A, std::vector<Row<KeyType>>& B, uint64_t i, uint64_t n){}

  static std::string name()  { return "StandardBinarySearch"; }
};
