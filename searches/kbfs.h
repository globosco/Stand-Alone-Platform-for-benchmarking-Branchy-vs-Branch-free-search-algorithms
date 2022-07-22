#pragma once
#include "search.h"

template <typename KeyType>
class KBFS_Search : public Search<KeyType> {
public:
  static uint64_t search( std::vector<Row<KeyType>>& data,
                   KeyType lookup_key, size_t start, size_t end, int k)  {
    
     // left is inclusive, right is exclusive
    uint64_t left = start, right = end;
    while (left < right)
    {
        //COUNT_ITERATION();
        // divide [left, right) in k segments
        uint64_t segmentLeft = left;
        uint64_t segmentRight = left + (right - left) / k;
        for (uint64_t i = 2; i <= k; ++i)
        {
          // advance to the next segment
                        uint64_t nextSeparatorIndex = left + (i * (right - left)) / k;
                        segmentLeft = lookup_key > data[segmentRight].key ? segmentRight + 1 : segmentLeft;
                        segmentRight = lookup_key > data[segmentRight].key ?  nextSeparatorIndex : segmentRight;  
        }
        left = segmentLeft;
        right = segmentRight;
    }

    uint64_t result = data[left].data[0];
    return result;
  }

  static void createLayout( std::vector<Row<KeyType>>& A, std::vector<Row<KeyType>>& B, uint64_t i, uint64_t n){}

  static std::string name()  {
    return "kbfs";
  }

};
