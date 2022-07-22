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
    #include "./competitors/PGM-index/include/pgm_index.hpp"

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

    double timer = 0;
    double buildTimer = 0;
    std::string searchName;
    int64_t ns;

    PGMIndex<uint64_t, 4> pgm4;
    PGMIndex<uint64_t, 8> pgm8;
    PGMIndex<uint64_t, 16> pgm16;
    PGMIndex<uint64_t, 32> pgm32;
    PGMIndex<uint64_t, 64> pgm64;
    PGMIndex<uint64_t, 256> pgm256;
    PGMIndex<uint64_t, 1024> pgm1024;
    PGMIndex<uint64_t, 2048> pgm2048;

    if(!strcmp(method, "bbs")){

        if(dataset == "L1_osm_cellids_200M"){
            pgm32 = PGMIndex<uint64_t,32>(A);
        }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_osm_cellids_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_books_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L2_fb_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_fb_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L2_wiki_ts_200M"){
            pgm16 = PGMIndex<uint64_t, 16>(A);
        }else if(dataset == "L4_wiki_ts_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else{
        pgm16 = PGMIndex<uint64_t, 16>(A);
        }

        ns = util::timing([&]{
            uint64_t res = 0;  
            for (uint64_t pos = 0; pos < Q.size(); pos++){
                ApproxPos bound;
                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    if(dataset == "L1_osm_cellids_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_osm_cellids_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_books_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_fb_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_fb_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_wiki_ts_200M"){
                        bound = pgm16.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_wiki_ts_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else{
                        bound = pgm16.find_approximate_position(Q[pos]);
                    }
                    StandardBinarySearchNoPrefetch<uint64_t>::search(data, Q[pos], bound.lo, bound.hi);
                }
            }
            });
        std::cout << "BBS TIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "StandardBinarySearchNoPrefetch";

    }else if(!strcmp(method, "bfs")){
        if(dataset == "L1_osm_cellids_200M"){
            pgm32 = PGMIndex<uint64_t,32>(A);
        }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_osm_cellids_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_books_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L2_fb_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_fb_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L2_wiki_ts_200M"){
            pgm16 = PGMIndex<uint64_t, 16>(A);
        }else if(dataset == "L4_wiki_ts_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else{
        pgm16 = PGMIndex<uint64_t, 16>(A);
        }
        
        ns = util::timing([&]{
            uint64_t res = 0;  
            for (uint64_t pos = 0; pos < Q.size(); pos++) {
                ApproxPos bound;
                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    if(dataset == "L1_osm_cellids_200M"){
                    bound = pgm32.find_approximate_position(Q[pos]);
                }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
                    bound = pgm4.find_approximate_position(Q[pos]);
                }else if(dataset == "L4_osm_cellids_200M"){
                    bound = pgm8.find_approximate_position(Q[pos]);
                }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
                    bound = pgm4.find_approximate_position(Q[pos]);
                }else if(dataset == "L4_books_200M"){
                    bound = pgm32.find_approximate_position(Q[pos]);
                }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
                    bound = pgm8.find_approximate_position(Q[pos]);
                }else if(dataset == "L2_fb_200M"){
                    bound = pgm4.find_approximate_position(Q[pos]);
                }else if(dataset == "L4_fb_200M"){
                    bound = pgm32.find_approximate_position(Q[pos]);
                }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
                    bound = pgm4.find_approximate_position(Q[pos]);
                }else if(dataset == "L2_wiki_ts_200M"){
                    bound = pgm16.find_approximate_position(Q[pos]);
                }else if(dataset == "L4_wiki_ts_200M"){
                    bound = pgm8.find_approximate_position(Q[pos]);
                }else{
                    bound = pgm16.find_approximate_position(Q[pos]);
                }
                    BranchlessBinarySearchNoPrefetch<uint64_t>::search(data, Q[pos],bound.lo, bound.hi);
                }
            }
        });
        
        std::cout << "BFS TIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "BranchlessBinarySearchNoPrefetch";
    }else if(!strcmp(method, "kbbs")){
        
        if(dataset == "L1_osm_cellids_200M"){
            pgm32 = PGMIndex<uint64_t,32>(A);
        }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_osm_cellids_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_books_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L2_fb_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_fb_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L2_wiki_ts_200M"){
            pgm16 = PGMIndex<uint64_t, 16>(A);
        }else if(dataset == "L4_wiki_ts_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else{
        pgm16 = PGMIndex<uint64_t, 16>(A);
        }
        ns = util::timing([&]{
            uint64_t res = 0;  
            for (uint64_t pos = 0; pos < Q.size(); pos++) {
                ApproxPos bound;
                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    if(dataset == "L1_osm_cellids_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_osm_cellids_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_books_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_fb_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_fb_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_wiki_ts_200M"){
                        bound = pgm16.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_wiki_ts_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else{
                        bound = pgm16.find_approximate_position(Q[pos]);
                    }
                        
                    KBBS_Search<uint64_t>::search(data, Q[pos], bound.lo, bound.hi,k);
                }
            }
        });
        std::cout << "KBBS With Prefetch TIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "kbbs";
    }else if(!strcmp(method, "fake")){
            
        if(dataset == "L1_osm_cellids_200M"){
            pgm32 = PGMIndex<uint64_t,32>(A);
        }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_osm_cellids_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_books_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else if(dataset == "L2_fb_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L4_fb_200M"){
            pgm32 = PGMIndex<uint64_t, 32>(A);
        }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
            pgm4 = PGMIndex<uint64_t, 4>(A);
        }else if(dataset == "L2_wiki_ts_200M"){
            pgm16 = PGMIndex<uint64_t, 16>(A);
        }else if(dataset == "L4_wiki_ts_200M"){
            pgm8 = PGMIndex<uint64_t, 8>(A);
        }else{
            pgm16 = PGMIndex<uint64_t, 16>(A);
        }
        ns = util::timing([&]{
            uint64_t res = 0;  
            for (uint64_t pos = 0; pos < Q.size(); pos++) {
                ApproxPos bound;
                if(Q[pos] > A[A.size()-1]){
                    res = A.size()-1;
                }else if(Q[pos] < A[0]){
                    res = 0;
                }else{
                    if(dataset == "L1_osm_cellids_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_osm_cellids_200M" || dataset == "L3_osm_cellids_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_osm_cellids_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else if(dataset == "L1_books_200M" || dataset == "L2_books_200M" || dataset == "L3_books_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_books_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }if(dataset == "L1_fb_200M" || dataset == "L3_fb_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_fb_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_fb_200M"){
                        bound = pgm32.find_approximate_position(Q[pos]);
                    }else  if(dataset == "L1_wiki_ts_200M" || dataset == "L3_wiki_ts_200M"){
                        bound = pgm4.find_approximate_position(Q[pos]);
                    }else if(dataset == "L2_wiki_ts_200M"){
                        bound = pgm16.find_approximate_position(Q[pos]);
                    }else if(dataset == "L4_wiki_ts_200M"){
                        bound = pgm8.find_approximate_position(Q[pos]);
                    }else{
                        bound = pgm16.find_approximate_position(Q[pos]);
                    }
                }
            }
        });
        
        std::cout << "FakeTIME: " << (double)ns/(double)Q.size() << std::endl;
        searchName = "FakeSearch";
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
    fout << "PGM" << "," << 0 << "," << (double)ns/(double)Q.size()
        << "," << 0 << "," << buildTimer/A.size() << "," << searchName
        << "," << dataNameStr << std::endl;

    fout.close();

    return 0;
    }
