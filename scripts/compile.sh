#Benchmark Ricerca
g++ ./benchmark.cpp -o ./benchmark -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O

#RMI 32 bit
g++ ./competitors/rmi/L1_books_200M_uint32_2.cpp -c -o ./competitors/rmi/L1_books_200M_uint32_2.o
g++ ./competitors/rmi/L2_books_200M_uint32_6.cpp -c -o ./competitors/rmi/L2_books_200M_uint32_6.o
g++ ./competitors/rmi/L3_books_200M_uint32_7.cpp -c -o ./competitors/rmi/L3_books_200M_uint32_7.o
g++ ./competitors/rmi/L4_books_200M_uint32_6.cpp -c -o ./competitors/rmi/L4_books_200M_uint32_6.o

#Benchmarch 32 bit
g++ ./benchmark_RMI_32.cpp ./competitors/rmi/L1_books_200M_uint32_2.o ./competitors/rmi/L2_books_200M_uint32_6.o ./competitors/rmi/L3_books_200M_uint32_7.o ./competitors/rmi/L4_books_200M_uint32_6.o -o ./benchmark_RMI_32 -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O
g++ ./benchmark_RMI_32_best.cpp ./competitors/rmi/L1_books_200M_uint32_2.o ./competitors/rmi/L2_books_200M_uint32_6.o ./competitors/rmi/L3_books_200M_uint32_7.o ./competitors/rmi/L4_books_200M_uint32_6.o -o ./benchmark_RMI_32_best -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O
g++ ./benchmark_RS_32_best.cpp -o ./benchmark_RS_32_best -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O
g++ ./benchmark_PGM_32_best.cpp -o ./benchmark_PGM_32_best -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O

#RMI 64 bit
g++ ./competitors/rmi/L1_books_200M_uint64_5.cpp -c -o ./competitors/rmi/L1_books_200M_uint64_5.o
g++ ./competitors/rmi/L2_books_200M_uint64_6.cpp -c -o ./competitors/rmi/L2_books_200M_uint64_7.o
g++ ./competitors/rmi/L3_books_200M_uint64_6.cpp -c -o ./competitors/rmi/L3_books_200M_uint64_6.o
g++ ./competitors/rmi/L4_books_200M_uint64_5.cpp -c -o ./competitors/rmi/L4_books_200M_uint64_5.o
g++ ./competitors/rmi/L1_fb_200M_uint64_7.cpp -c -o ./competitors/rmi/L1_fb_200M_uint64_7.o
g++ ./competitors/rmi/L2_fb_200M_uint64_7.cpp -c -o ./competitors/rmi/L2_fb_200M_uint64_7.o
g++ ./competitors/rmi/L3_fb_200M_uint64_7.cpp -c -o ./competitors/rmi/L3_fb_200M_uint64_7.o
g++ ./competitors/rmi/L4_fb_200M_uint64_0.cpp -c -o ./competitors/rmi/L4_fb_200M_uint64_0.o
g++ ./competitors/rmi/L1_osm_cellids_200M_uint64_2.cpp -c -o ./competitors/rmi/L1_osm_cellids_200M_uint64_2.o
g++ ./competitors/rmi/L1_osm_cellids_200M_uint64_4.cpp -c -o ./competitors/rmi/L1_osm_cellids_200M_uint64_4.o
g++ ./competitors/rmi/L2_osm_cellids_200M_uint64_4.cpp -c -o ./competitors/rmi/L2_osm_cellids_200M_uint64_4.o
g++ ./competitors/rmi/L3_osm_cellids_200M_uint64_4.cpp -c -o ./competitors/rmi/L3_osm_cellids_200M_uint64_4.o
g++ ./competitors/rmi/L3_osm_cellids_200M_uint64_3.cpp -c -o ./competitors/rmi/L3_osm_cellids_200M_uint64_3.o
g++ ./competitors/rmi/L2_osm_cellids_200M_uint64_5.cpp -c -o ./competitors/rmi/L2_osm_cellids_200M_uint64_5.o
g++ ./competitors/rmi/L3_osm_cellids_200M_uint64_5.cpp -c -o ./competitors/rmi/L3_osm_cellids_200M_uint64_5.o
g++ ./competitors/rmi/L4_osm_cellids_200M_uint64_0.cpp -c -o ./competitors/rmi/L4_osm_cellids_200M_uint64_0.o
g++ ./competitors/rmi/L1_wiki_ts_200M_uint64_6.cpp -c -o ./competitors/rmi/L1_wiki_ts_200M_uint64_6.o
g++ ./competitors/rmi/L2_wiki_ts_200M_uint64_6.cpp -c -o ./competitors/rmi/L2_wiki_ts_200M_uint64_6.o
g++ ./competitors/rmi/L3_wiki_ts_200M_uint64_5.cpp -c -o ./competitors/rmi/L3_wiki_ts_200M_uint64_5.o
g++ ./competitors/rmi/L4_wiki_ts_200M_uint64_0.cpp -c -o ./competitors/rmi/L4_wiki_ts_200M_uint64_0.o
#Benchmark 64 bit
g++ ./benchmark_RMI_best.cpp ./competitors/rmi/L1_books_200M_uint64_5.o ./competitors/rmi/L2_books_200M_uint64_6.o ./competitors/rmi/L3_books_200M_uint64_6.o ./competitors/rmi/L4_books_200M_uint64_5.o ./competitors/rmi/L1_fb_200M_uint64_7.o ./competitors/rmi/L2_fb_200M_uint64_7.o ./competitors/rmi/L3_fb_200M_uint64_7.o ./competitors/rmi/L4_fb_200M_uint64_0.o ./competitors/rmi/L1_osm_cellids_200M_uint64_2.o ./competitors/rmi/L1_osm_cellids_200M_uint64_4.o ./competitors/rmi/L2_osm_cellids_200M_uint64_5.o ./competitors/rmi/L3_osm_cellids_200M_uint64_5.o ./competitors/rmi/L3_osm_cellids_200M_uint64_4.o ./competitors/rmi/L2_osm_cellids_200M_uint64_4.o ./competitors/rmi/L3_osm_cellids_200M_uint64_3.o ./competitors/rmi/L4_osm_cellids_200M_uint64_0.o ./competitors/rmi/L1_wiki_ts_200M_uint64_6.o ./competitors/rmi/L2_wiki_ts_200M_uint64_6.o ./competitors/rmi/L3_wiki_ts_200M_uint64_5.o ./competitors/rmi/L4_wiki_ts_200M_uint64_0.o -o ./benchmark_RMI_best -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O

g++ ./benchmark_PGM_best.cpp -o ./benchmark_PGM_best -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O

g++ ./benchmark_RS_best.cpp -o ./benchmark_RS_best -ffast-math -Wall -Wfatal-errors -march=native -fopenmp -g -O
