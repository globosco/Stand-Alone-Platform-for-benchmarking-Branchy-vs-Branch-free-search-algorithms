#pragma once
#include "search.h"

template <typename KeyType>
class EytzingerLayoutSearch : public Search<KeyType> {
 private:
   static uint64_t eytzeingerArray(std::vector<Row<KeyType>>& A, std::vector<Row<KeyType>>& B, uint64_t Aidx, uint64_t i, uint64_t n){
         if(i >= n) return Aidx;
         // std::cout << "Richiamo..." <<i << std::endl;
         Aidx = eytzeingerArray(A, B, Aidx,  2*i+1, n);
         //std::cout << "SIAMO in..." << Aidx << std::endl;
         // std::cout << (A[Aidx+1].key) << " " << i << std::endl;
         //B[i] = A[Aidx++];
         B[i] =  A[Aidx++];
        //  std::cout << (B[i].key) << " " << i << std::endl;
         //std::cout << "B: " << (B.begin() +i)->data[0] << std::endl;

         Aidx = eytzeingerArray(A, B, Aidx, 2*i+2, n);

         return Aidx;
     }

 public:
  static uint64_t search( std::vector<Row<KeyType>>& data,
                   KeyType lookup_key,
                  size_t start, size_t end)  {

    uint64_t i = 0;
    uint64_t n = end - start + 1;
    uint64_t multiplier = 128;
    uint64_t offset = 3*multiplier/2-1;

    while (i < n) {
        __builtin_prefetch(&(data[multiplier*i + offset]),  0, 0);
            // cout << i << " " << data[i] << " " << x << endl;
        i = (lookup_key <= data[i].key) ? (2*i + 1) : (2*i + 2);
    }
    uint64_t j = (i+1) >> __builtin_ffs(~(i+1));
    uint64_t lower = (j == 0) ? n : j-1;
    // std::cout << "Indice trovato: " << j << std::endl;
    // std::cout <<  "Sto cercando " << lookup_key << "  Ho trovato " << data[j-1].key  << std::endl;
    return lower;
  }

  static void createLayout( std::vector<Row<KeyType>>& A, std::vector<Row<KeyType>>& B, uint64_t i, uint64_t n){
    //std::cout << "DIMENSIONE LAYOUT " << B.size() << std::endl;
    eytzeingerArray(A, B, 0, i, n);
    //std::cout << "DIMENSIONE LAYOUT " << B.size() << std::endl;
    // auto it = B.begin();
    // while (it++ != B.end()) {
    //   std::cout << it->data[0] << std::endl;
    // }
  }

  static const std::string name() { return "EytzingerLayoutSearch"; }
};
