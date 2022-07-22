
# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m bbs
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m bbs
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m bbs
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m bbs
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m bbs

# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m bbsp
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m bbsp
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m bbsp
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m bbsp
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m bbsp

# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m bfs
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m bfs
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m bfs
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m bfs
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m bfs

# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m bfsp
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m bfsp
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m bfsp
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m bfsp
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m bfsp

# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m bfe
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m bfe
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m bfe
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m bfe
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m bfe

# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m bfep
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m bfep
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m bfep
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m bfep
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m bfep


# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m kbbs
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m kbbs
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m kbbs
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m kbbs
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m kbbs


# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m kbfs
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m kbfs
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m kbfs
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m kbfs
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m kbfs


# for i in $(seq 4 1 28)
# do
#   ./benchmark -p data/ -d uniform_$i -o results/ -m lower_bound
# done
./benchmark -p data/ -d L1_osm_cellids_200M -o results/ -m lower_bound
./benchmark -p data/ -d L2_osm_cellids_200M -o results/ -m lower_bound
./benchmark -p data/ -d L3_osm_cellids_200M -o results/ -m lower_bound
./benchmark -p data/ -d L4_osm_cellids_200M -o results/ -m lower_bound
