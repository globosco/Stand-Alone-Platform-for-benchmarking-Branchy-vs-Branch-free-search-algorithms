#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>

#define ROW_WIDTH 1

/**

Utility functions and strucures implemented on SOSD: Benchmark Platform
available at: https://github.com/learnedsystems/SOSD

*/

//#define PRINT_ERRORS

enum DataType { UINT32 = 0, UINT64 = 1 };

template <class KeyType>
struct KeyValue {
  KeyType key;
  uint64_t value;
} __attribute__((packed));

template <class KeyType>
struct Row {
  KeyType key;
  uint64_t data[ROW_WIDTH];
};

template <class KeyType = uint64_t>
struct EqualityLookup {
  KeyType key;
  uint64_t result;
};

struct SearchBound {
  size_t start;
  size_t stop;
};

namespace util {

  static uint64_t timing(std::function<void()> fn) {

    std::cout << "Calcolo Tempi" << std::endl;

    const auto start = std::chrono::high_resolution_clock::now();
    fn();
    std::cout << "Calcolo Tempi" << std::endl;
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
        .count();
    // return 0;
  }


  // Loads values from binary file into vector.
  template <typename T>
  static std::vector<T> load_data(const std::string& filename,
                                  bool print = true) {
    std::vector<T> data;
    uint64_t ns = 0;

    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
      std::cerr << "unable to open " << filename << std::endl;
      exit(EXIT_FAILURE);
    }
    // Read size.
    uint64_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(uint64_t));
    // std::cout << size << std::endl;
    data.resize(size);
    // Read values.
    in.read(reinterpret_cast<char*>(data.data()), size * sizeof(T));
    in.close();

    const uint64_t ms = ns / 1e6;

    if (print) {
      std::cout << "read " << data.size() << " values from " << filename << " in "
                << ms << " ms (" << static_cast<double>(data.size()) / 1000 / ms
                << " M values/s)" << std::endl;
    }

    return data;
  }

  // Writes values from vector into binary file.
  template <typename T>
  static void write_data(const std::vector<T>& data, const std::string& filename,
                         const bool print = true) {
    const uint64_t ns = util::timing([&] {
      std::ofstream out(filename, std::ios_base::trunc | std::ios::binary);
      if (!out.is_open()) {
        std::cerr << "unable to open " << filename << std::endl;
        exit(EXIT_FAILURE);
      }
      // Write size.
      const uint64_t size = data.size();
      out.write(reinterpret_cast<const char*>(&size), sizeof(uint64_t));
      // Write values.
      out.write(reinterpret_cast<const char*>(data.data()), size * sizeof(T));
      out.close();
    });
    const uint64_t ms = ns / 1e6;
    if (print) {
      std::cout << "wrote " << data.size() << " values to " << filename << " in "
                << ms << " ms (" << static_cast<double>(data.size()) / 1000 / ms
                << " M values/s)" << std::endl;
    }
  }

  // Returns a value for a key at position i.
  template <class KeyType>
  static uint64_t get_value(const KeyType i) {
    return i;
  }

  //Get Option from CMD Input
  static char* getCmdOption(char ** begin, char ** end, const std::string & option)
  {
      char ** itr = std::find(begin, end, option);
      if (itr != end && ++itr != end)
      {
          return *itr;
      }
      return 0;
  }

  //Check if Option from CMD Input exists
  static bool cmdOptionExists(char** begin, char** end, const std::string& option)
  {
      return std::find(begin, end, option) != end;
  }

  template <class KeyType>
  static std::vector<Row<KeyType>> add_values(const std::vector<KeyType>& keys) {
    std::vector<Row<KeyType>> result;
    result.reserve(keys.size());

    for (uint64_t i = 0; i < keys.size(); ++i) {
      Row<KeyType> row;
      row.key = keys[i];
      for (int j = 0; j < ROW_WIDTH; j++) {
        row.data[j] = get_value(i * (j + 1));
      }

      result.push_back(row);
    }
    return result;
  }
}  // namespace util
