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
          strcmp(method, "kbbs") && strcmp(method, "kbfs") && strcmp(method, "fake")){
          std::cerr << "Method name Invalid...Aborting..." << std::endl;
          return 1;
      }
  }

  //Exponent parameter
  if(util::cmdOptionExists(argv, argv+argc, "-k")){
      nKary = util::getCmdOption(argv, argv + argc, "-k");
  }else{
      nKary = NULL;
  }

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
      ss << dataName << "_uint32_equality_lookups_1M_single";
      QFn = ss.str();
      ss.str("");
      ss.clear();
  }else{
      ss << path << "Query/" << dataName << "_uint32_equality_lookups_2M_single";
      QFn = ss.str();
      ss.str("");
      ss.clear();
  }
  if(path == NULL){
      ss << dataName << "_uint32";
      AFn = ss.str();
      ss.str("");
      ss.clear();
  }else{
      ss << path << dataName << "_uint32";
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

  std::vector<uint32_t> A = util::load_data<uint32_t>(AFn);
  std::vector<uint32_t> Q = util::load_data<uint32_t>(QFn);

  std::vector<Row<uint32_t>> data;

  data = util::add_values<uint32_t>(A);

  

  double timer = 0;
  double buildTimer = 0;
  std::string searchName;
  int64_t ns;

    if(!strcmp(method, "bbs")){

        uint64_t res = 0;  
        if(dataset == "L1_books_200M"){
            const char * path = "rmi_data";
            L1_books_200M_uint32_2::load(path);
        }else if(dataset == "L2_books_200M"){
            const char * path = "rmi_data";
            L2_books_200M_uint32_6::load(path);
        }else if(dataset == "L3_books_200M"){
            const char * path = "rmi_data";
            L3_books_200M_uint32_7::load(path);
        }else if(dataset == "L4_books_200M"){
            const char * path = "rmi_data";
            L4_books_200M_uint32_6::load(path);
        }
    
        ns = util::timing([&]{
            for (uint64_t pos = 0; pos < Q.size(); pos++){

                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    SearchBound bound;
                    if(dataset == "L1_books_200M"){
                        size_t err;
                        uint64_t guess = L1_books_200M_uint32_2::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L2_books_200M"){
                        size_t err;
                        uint64_t guess = L2_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L3_books_200M"){
                        size_t err;
                        uint64_t guess = L3_books_200M_uint32_7::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L4_books_200M"){
                        size_t err;
                        uint64_t guess = L4_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }
                    StandardBinarySearchNoPrefetch<uint32_t>::search(data, Q[pos], 0, A.size()-1);
                }
            }
        });
        std::cout << "BBS TIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "StandardBinarySearchNoPrefetch";
    if(!strcmp(method, "bfs")){

        uint64_t res = 0;  
        if(dataset == "L1_books_200M"){
            const char * path = "rmi_data";
            L1_books_200M_uint32_2::load(path);
        }else if(dataset == "L2_books_200M"){
            const char * path = "rmi_data";
            L2_books_200M_uint32_6::load(path);
        }else if(dataset == "L3_books_200M"){
            const char * path = "rmi_data";
            L3_books_200M_uint32_7::load(path);
        }else if(dataset == "L4_books_200M"){
            const char * path = "rmi_data";
            L4_books_200M_uint32_6::load(path);
        }
        ns = util::timing([&]{
            for (uint32_t pos = 0; pos < Q.size(); pos++) {

                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    SearchBound bound;
                    if(dataset == "L1_books_200M"){
                        size_t err;
                        uint64_t guess = L1_books_200M_uint32_2::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L2_books_200M"){
                        size_t err;
                        uint64_t guess = L2_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L3_books_200M"){
                        size_t err;
                        uint64_t guess = L3_books_200M_uint32_7::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L4_books_200M"){
                        size_t err;
                        uint64_t guess = L4_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }
                BranchlessBinarySearchNoPrefetch<uint32_t>::search(data, Q[pos], 0, A.size()-1);
                }
            }
        });
        std::cout << "BFS TIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "BranchlessBinarySearchNoPrefetch";
    }else if(!strcmp(method, "kbbs")){
        uint64_t res = 0;  
        if(dataset == "L1_books_200M"){
            const char * path = "rmi_data";
            L1_books_200M_uint32_2::load(path);
        }else if(dataset == "L2_books_200M"){
            const char * path = "rmi_data";
            L2_books_200M_uint32_6::load(path);
        }else if(dataset == "L3_books_200M"){
            const char * path = "rmi_data";
            L3_books_200M_uint32_7::load(path);
        }else if(dataset == "L4_books_200M"){
            const char * path = "rmi_data";
            L4_books_200M_uint32_6::load(path);
        }
        ns = util::timing([&]{
            for (uint64_t pos = 0; pos < Q.size(); pos++) {
                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    SearchBound bound;
                    if(dataset == "L1_books_200M"){
                        size_t err;
                        uint64_t guess = L1_books_200M_uint32_2::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L2_books_200M"){
                        size_t err;
                        uint64_t guess = L2_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L3_books_200M"){
                        size_t err;
                        uint64_t guess = L3_books_200M_uint32_7::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L4_books_200M"){
                        size_t err;
                        uint64_t guess = L4_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }
                    KBBS_Search<uint32_t>::search(data, Q[pos], bound.start, bound.stop,k);
                }
            }
        });
        std::cout << "KBBS With Prefetch TIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "kbbs";
    }else if(!strcmp(method, "fake")){
        
        uint64_t res = 0;  
        if(dataset == "L1_books_200M"){
            const char * path = "rmi_data";
            L1_books_200M_uint32_2::load(path);
        }else if(dataset == "L2_books_200M"){
            const char * path = "rmi_data";
            L2_books_200M_uint32_6::load(path);
        }else if(dataset == "L3_books_200M"){
            const char * path = "rmi_data";
            L3_books_200M_uint32_7::load(path);
        }else if(dataset == "L4_books_200M"){
            const char * path = "rmi_data";
            L4_books_200M_uint32_6::load(path);
        }
        ns = util::timing([&]{
            for (uint64_t pos = 0; pos < Q.size(); pos++) {
                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    SearchBound bound;
                    if(dataset == "L1_books_200M"){
                        size_t err;
                        uint64_t guess = L1_books_200M_uint32_2::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L2_books_200M"){
                        size_t err;
                        uint64_t guess = L2_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L3_books_200M"){
                        size_t err;
                        uint64_t guess = L3_books_200M_uint32_7::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }else if(dataset == "L4_books_200M"){
                        size_t err;
                        uint64_t guess = L4_books_200M_uint32_6::lookup(Q[pos], &err);
                        uint64_t start = (guess < err ? 0 : guess - err);
                        uint64_t stop = (guess + err >= A.size() ? A.size() : guess + err);

                        bound.start = start; 
                        bound.stop = stop;
                    }            
                }
            }
        });
        std::cout << "Prediction TIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "FakeSearch";
    }
    ss << dataName;
    std::string dataNameStr;
    ss >> dataNameStr;
    ss.clear();

    const std::string filename =
        "./results/" + dataNameStr + "_uint32_results_table.csv";

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
