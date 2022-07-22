#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include "util.h"
#include "./searches/branching_binary_search.h"
#include "./searches/standard_binary_search.h"
#include "./searches/standard_binary_search_no_prefetch.h"
#include "./searches/branchless_binary_search.h"
#include "./searches/branchless_binary_search_no_prefetch.h"
#include "./searches/eytzinger_layout_search.h"
#include "./searches/eytzinger_layout_search_no_prefetch.h"
#include "./searches/kbbs.h"
#include "./searches/kbfs.h"
#include "./competitors/rmi/all_rmis.h"

using namespace std;

int main(int argc, char* argv[]){

  char *dataName, *outputPath, *path, *method, *type, *nKary;
  int align, shuffle, sort;

  std::cout << "Check Parameters..." << std::endl;

  //Print help
  if(util::cmdOptionExists(argv, argv+argc, "-h"))
  {
      std::cout << "Help"<< std::endl;
      return 0;
  }

  //Check Input Path parameter
  if(!util::cmdOptionExists(argv, argv+argc, "-p"))
  {
      path = NULL;
  }else{
      path = util::getCmdOption(argv, argv + argc, "-p");
      if(!path || !strncmp ( path, "-", 1 )){
          path = NULL;
      }
  }


  //Check Dataset name parameter
  if(!util::cmdOptionExists(argv, argv+argc, "-d"))
  {
      std::cerr << "Dataset name missed...Aborting..." << std::endl;
      return 1;
  }else{
      dataName = util::getCmdOption(argv, argv + argc, "-d");
      if(!dataName || !strncmp ( dataName, "-", 1 )){
          std::cerr << "Dataset name missed...Aborting..." << std::endl;
          return 1;
      }
  }

  //Check Output path and filename parameter
  if(!util::cmdOptionExists(argv, argv+argc, "-o"))
  {
      std::cerr << "Output filename missed...Aborting..." << std::endl;
      return 1;
  }else{
      outputPath = util::getCmdOption(argv, argv + argc, "-o");
      if(!outputPath || !strncmp ( outputPath, "-", 1 )){
          std::cerr << "Output file path missed...Aborting..." << std::endl;
          return 1;
      }
  }

  //Check Method Name parameter
  if(!util::cmdOptionExists(argv, argv+argc, "-m"))
  {
      std::cerr << "Method Name Missed...Aborting..." << std::endl;
      return 1;
  }else{
      method = util::getCmdOption(argv, argv + argc, "-m");
      if(!method || !strncmp ( method, "-", 1 )){
          std::cerr << "Method name Missed...Aborting..." << std::endl;
          return 1;
      }
      if(strcmp(method, "bbs") && strcmp(method, "bfs") && strcmp(method, "bbsp") && strcmp(method, "bfsp") &&
          strcmp(method, "bfe") && strcmp(method, "bfep") && strcmp(method, "lower_bound") &&
          strcmp(method, "kbbs") && strcmp(method, "kbfs")){
          std::cerr << "Method name Invalid...Aborting..." << std::endl;
          return 1;
      }
  }

  //Integer Type parameter
  // if(!util::cmdOptionExists(argv, argv+argc, "-t"))
  // {
  //     std::cerr << "Integer Type Missed...Aborting..." << std::endl;
  //     return 1;
  // }else{
  //     type = util::getCmdOption(argv, argv + argc, "-t");
  //     if(!type || !strncmp ( type, "-", 1 )){
  //         std::cerr << "Integer Type Missed...Aborting..." << std::endl;
  //         return 1;
  //     }
  //     // cout << type << endl;
  //     // cout <<  strcmp(type, "uint64");
  //     // cout << strcmp(type, "uint32");
  //     if(strcmp(type, "uint64") && strcmp(type, "uint32")){
  //         std::cerr << "Integer Type Invalid...Aborting..." << std::endl;
  //         return 1;
  //     }
  // }

  //Exponent parameter
  if(util::cmdOptionExists(argv, argv+argc, "-k")){
      nKary = util::getCmdOption(argv, argv + argc, "-k");
  }else{
      nKary = NULL;
  }

  // //Check align memory params
  // if(!util::cmdOptionExists(argv, argv+argc, "-a"))
  // {
  //     align=0;
  // }else{
  //     align=1;
  // }
  //
  // //Check shuffle data params
  // if(!util::cmdOptionExists(argv, argv+argc, "-sh"))
  // {
  //     shuffle=0;
  // }else{
  //     shuffle=1;
  // }
  //
  // //Check sorting data params
  // if(!util::cmdOptionExists(argv, argv+argc, "-so"))
  // {
  //     sort=0;
  // }else{
  //     sort=1;
  // }


  /*
  *
  * Creating Filename from params
  *
  */
  std::stringstream ss;
  std::string wFn, bFn, oFn, QFn, AFn, BFn;
  std::string dataset;
  int k=3;
  ss.str("");
  ss.clear();

  if(path == NULL){
      ss << dataName << "_uint64_equality_lookups_1M_single";
      QFn = ss.str();
      ss.str("");
      ss.clear();
  }else{
      ss << path << "Query/" << dataName << "_uint64_equality_lookups_2M_single";
      QFn = ss.str();
      ss.str("");
      ss.clear();
  }
  if(path == NULL){
      ss << dataName << "_uint64";
      AFn = ss.str();
      ss.str("");
      ss.clear();
  }else{
      ss << path << dataName << "_uint64";
      AFn = ss.str();
      ss.str("");
      ss.clear();
  }

  ss << outputPath << dataName << ".std.out" <<".csv";
  oFn = ss.str();
  ss.str("");
  ss.clear();

  if(nKary != NULL){
    k = stoi(nKary);
  }

    ss << dataName;
    dataset = ss.str();
    ss.str("");
    ss.clear();

  std::vector<uint64_t> A = util::load_data<uint64_t>(AFn);
  std::vector<uint64_t> Q = util::load_data<uint64_t>(QFn);

  std::vector<Row<uint64_t>> data;

  data = util::add_values<uint64_t>(A);

  // for (uint64_t pos = 0; pos < A.size(); pos++) {
  //   index_data_.push_back((Row<uint64_t>){A[pos], pos});
  // }

  // for (uint64_t pos = 0; pos < A.size(); pos++) {
  //   std::cout << data[pos].key << " -> " << data[pos].data[0] << std::endl;
  // }

  double timer = 0;
  double buildTimer = 0;
  std::string searchName;
  int64_t ns;

  if(!strcmp(method, "lower_bound")){
    // const auto start = std::chrono::high_resolution_clock::now();
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++) {
        BranchingBinarySearch<uint64_t>::search(data, Q[pos], 0, A.size()-1);
        }
    });
    // const auto end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << ns << " " << Q.size() << std::endl;
    std::cout << "Lower_Bound TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "LowerBoundSearch";
  }else if(!strcmp(method, "bbs")){
    uint64_t res = 0;
    if(dataset == "L1_osm_cellids_200M"){
        const char * path = "rmi_data";
        L1_osm_cellids_200M_uint64_2::load(path);
    }else if(dataset == "L2_osm_cellids_200M"){
        const char * path = "rmi_data";
        L2_osm_cellids_200M_uint64_5::load(path);
    }else if(dataset == "L3_osm_cellids_200M"){
        const char * path = "rmi_data";
        L3_osm_cellids_200M_uint64_5::load(path);
    }else if(dataset == "L4_osm_cellids_200M"){
        const char * path = "rmi_data";
        L4_osm_cellids_200M_uint64_0::load(path);
    }
       
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++){
            if(Q[pos] > A[A.size()-1]){
                res = A.size()-1;
            }else if(Q[pos] < A[0]){
                res = 0;
            }else{ 
                SearchBound bound;
                if(dataset == "L1_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L1_osm_cellids_200M_uint64_2::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L2_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L2_osm_cellids_200M_uint64_5::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L3_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L3_osm_cellids_200M_uint64_5::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L4_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L4_osm_cellids_200M_uint64_0::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }
                res  = StandardBinarySearch<uint64_t>::search(data, Q[pos], bound.start,bound.stop);
            }
        }
      });
    // // const auto start = std::chrono::high_resolution_clock::now();
    // // for (uint64_t pos = 0; pos < Q.size(); pos++) {
    // //   StandardBinarySearchNoPrefetch<uint64_t>::search(data, Q[pos], 0, A.size()-1);
    // // }
    // // const auto end = std::chrono::high_resolution_clock::now();
    // std::cout << "Start: " << start.time_since_epoch().count() << std::endl;
    // std::cout << "End: " << end.time_since_epoch().count() << std::endl;
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "BBS TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "StandardBinarySearchNoPrefetch";
  }else if(!strcmp(method, "bbsp")){
    // const auto start = std::chrono::high_resolution_clock::now();
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++) {
        StandardBinarySearch<uint64_t>::search(data, Q[pos], 0, A.size()-1);
        }
    });
    // const auto end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "BBS With Prefetch TIME: " << (double)timer/(double)Q.size() << std::endl;
    searchName = "StandardBinarySearch";
  }else if(!strcmp(method, "bfs")){
    uint64_t res = 0;
    if(dataset == "L1_osm_cellids_200M"){
        cout << "CCarico parametri" << endl;
        const char * path = "rmi_data";
        L1_osm_cellids_200M_uint64_4::load(path);
    }else if(dataset == "L2_osm_cellids_200M"){
        const char * path = "rmi_data";
        L2_osm_cellids_200M_uint64_5::load(path);
    }else if(dataset == "L3_osm_cellids_200M"){
        const char * path = "rmi_data";
        L3_osm_cellids_200M_uint64_4::load(path);
    }else if(dataset == "L4_osm_cellids_200M"){
        const char * path = "rmi_data";
        L4_osm_cellids_200M_uint64_0::load(path);
    }
    // const auto start = std::chrono::high_resolution_clock::now();
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++) {SearchBound bound;
            if(Q[pos] > A[A.size()-1]){
                res = A.size()-1;
            }else if(Q[pos] < A[0]){
                res = 0;
            }else{
                if(dataset == "L1_osm_cellids_200M"){
                   
                    size_t err;
                    uint64_t guess = L1_osm_cellids_200M_uint64_4::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L2_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L2_osm_cellids_200M_uint64_5::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L3_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L3_osm_cellids_200M_uint64_4::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L4_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L4_osm_cellids_200M_uint64_0::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }
                BranchlessBinarySearchNoPrefetch<uint64_t>::search(data, Q[pos], bound.start, bound.stop);
            }
        }
    });
    // const auto end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "BFS TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "BranchlessBinarySearchNoPrefetch";
  }else if(!strcmp(method, "bfsp")){
    // const auto start = std::chrono::high_resolution_clock::now();
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++) {
          // std::cout << pos << std::endl;
        BranchlessBinarySearch<uint64_t>::search(data, Q[pos], 0, A.size()-1);
        }
    });
    // const auto end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "BFS With Prefetch TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "BranchlessBinarySearch";
  }else if(!strcmp(method, "kbbs")){
    // const auto start = std::chrono::high_resolution_clock::now();
    uint64_t res = 0;
    if(dataset == "L1_osm_cellids_200M"){
        const char * path = "rmi_data";
        L1_osm_cellids_200M_uint64_2::load(path);
    }else if(dataset == "L2_osm_cellids_200M"){
        const char * path = "rmi_data";
        L2_osm_cellids_200M_uint64_4::load(path);
    }else if(dataset == "L3_osm_cellids_200M"){
        const char * path = "rmi_data";
        L3_osm_cellids_200M_uint64_3::load(path);
    }else if(dataset == "L4_osm_cellids_200M"){
        const char * path = "rmi_data";
        L4_osm_cellids_200M_uint64_0::load(path);
    }
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++){
            if(Q[pos] > A[A.size()-1]){
                res = A.size()-1;
            }else if(Q[pos] < A[0]){
                res = 0;
            }else{
                
                SearchBound bound;
                if(dataset == "L1_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L1_osm_cellids_200M_uint64_2::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L2_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L2_osm_cellids_200M_uint64_4::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L3_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L3_osm_cellids_200M_uint64_3::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }else if(dataset == "L4_osm_cellids_200M"){
                    size_t err;
                    uint64_t guess = L4_osm_cellids_200M_uint64_0::lookup(Q[pos], &err);
                    uint64_t start = (guess < err ? 0 : guess - err);
                    uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                    bound.start = start; 
                    bound.stop = stop;
                }
                res = KBBS_Search<uint64_t>::search(data, Q[pos], bound.start, bound.stop,k);
            }
        }
    });
    // const auto end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "KBBS With Prefetch TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "kbbs";
  }else if(!strcmp(method, "kbfs")){
    // const auto start = std::chrono::high_resolution_clock::now();
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++) {
        KBFS_Search<uint64_t>::search(data, Q[pos], 0, A.size()-1, k);
        }
    });
    // const auto end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "KBFS With Prefetch TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "kbfs";
  }else if(!strcmp(method, "bfep")){

    std::vector<Row<uint64_t>> layout;
    layout.resize(A.size());

    auto start = std::chrono::high_resolution_clock::now();
    EytzingerLayoutSearch<uint64_t>::createLayout(data, layout, 0, A.size());
    auto end = std::chrono::high_resolution_clock::now();
    buildTimer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // start = std::chrono::high_resolution_clock::now();
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++) {
        EytzingerLayoutSearch<uint64_t>::search(data, Q[pos], 0, A.size()-1);
        }
    });
    // end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "KBFS With Prefetch TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "EytzingerLayoutSearch";
  }else if(!strcmp(method, "bfe")){

    std::vector<Row<uint64_t>> layout;
    layout.resize(A.size());

    auto start = std::chrono::high_resolution_clock::now();
    EytzingerLayoutSearchNoPrefetch<uint64_t>::createLayout(data, layout, 0, A.size());
    auto end = std::chrono::high_resolution_clock::now();
    buildTimer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // start = std::chrono::high_resolution_clock::now();
    ns = util::timing([&]{
        for (uint64_t pos = 0; pos < Q.size(); pos++) {
        EytzingerLayoutSearchNoPrefetch<uint64_t>::search(data, Q[pos], 0, A.size()-1);
        }
    });
    // end = std::chrono::high_resolution_clock::now();
    // timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "KBFS With Prefetch TIME: " << (double)ns/(double)Q.size() << std::endl;
    searchName = "EytzingerLayoutSearchNoPrefetch";
  }
    ss << dataName;
    std::string dataNameStr;
    ss >> dataNameStr;
    ss.clear();

    const std::string filename =
        "./results/" + dataNameStr + "_results_table.csv";

    std::ofstream fout(filename, std::ofstream::out | std::ofstream::app);

    if (!fout.is_open()) {
      std::cerr << "Failure to print CSV on " << filename << std::endl;
      return 1;
    }

    std::cout << timer << std::endl;
    fout << "RMI" << "," << 0 << "," << (double)ns/(double)Q.size()
        << "," << 0 << "," << buildTimer/A.size() << "," << searchName
        << "," << dataNameStr << std::endl;

    fout.close();

  return 0;
}
