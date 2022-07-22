# Stand-Alone-Platform-for-benchmarking-Branchy-vs-Branch-free-search-algorithms



## Datasets

Datasets used in this work can be downloaded at https://math.unipa.it/lobosco/LSTS/
All downloaded files must be placed in the data folder located in the repository root before running the benchmark scripts.

## Usage instructions

We provide a number of scripts to automate things. Each is located in the `scripts` directory, but should be executed from the repository root.

## Running the benchmark

* `./scripts/build_rmis.sh` compiles and builds the RMIs for each dataset
* `./scripts/prepare.sh` constructs query workloads and compiles the benchmark
* `./scripts/execute_all.sh` executes the benchmark on each workload and with all the search methods used in the work, storing the results in `results`. This script returns the results as csv files.

## Cite

If you use this benchmark in your own work, please cite us:

```
@misc{amato2022standard,
      title={Standard Vs Uniform Binary Search and Their Variants in Learned Static Indexing: The Case of the Searching on Sorted Data Benchmarking Software Platform}, 
      author={Domenico Amato and Giosuè Lo Bosco and Raffaele Giancarlo},
      year={2022},
      eprint={2201.01554},
      archivePrefix={arXiv},
      primaryClass={cs.DS}
}
