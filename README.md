# Stand-Alone-Platform-for-benchmarking-Branchy-vs-Branch-free-search-algorithms



## Datasets

Datasets used in this work can be downloaded at https://osf.io/ygnw8/?view_only=f531d074c25b4d3c92df6aec97558b39.
All downloaded files must be placed in the data folder located in the repository root before running the benchmark scripts.

## Prerequisites

In order to execute this benchmark, you have to download rmi data folder from ... and copy it in the repository root.

## Usage instructions

We provide a number of scripts to automate things. Each is located in the `scripts` directory, but should be executed from the repository root.

### Running the benchmark

* `./scripts/compile.sh` compiles the benchmark
* `./scripts/execute_search_all.sh` executes the benchmark using all the search methods used in the work without Learned Index, storing the results in `results`. This script returns the results as csv files.
* `./scripts/execute_best_all.sh` executes the benchmark using all the search methods used in the work with the best performing Learned Indexes, storing the results in `results`. This script returns the results as csv files.

## Cite

If you use this benchmark in your own work, please cite us:

```

@article{https://doi.org/10.1002/spe.3150,
      author = {Amato, Domenico and Lo Bosco, Giosué and Giancarlo, Raffaele},
      title = {Standard versus uniform binary search and their variants in learned static indexing: The case of the searching on sorted data benchmarking software platform},
      journal = {Software: Practice and Experience},
      volume = {53},
      number = {2},
      pages = {318-346},
      keywords = {algorithms with prediction, binary search variants, learned index structures, search on sorted data platform},
      doi = {https://doi.org/10.1002/spe.3150},
      url = {https://onlinelibrary.wiley.com/doi/abs/10.1002/spe.3150},
      eprint = {https://onlinelibrary.wiley.com/doi/pdf/10.1002/spe.3150},
      year = {2023}
}

```

@misc{amato2022standard,
      title={Standard Vs Uniform Binary Search and Their Variants in Learned Static Indexing: The Case of the Searching on Sorted Data Benchmarking Software Platform}, 
      author={Domenico Amato and Giosuè Lo Bosco and Raffaele Giancarlo},
      year={2022},
      eprint={2201.01554},
      archivePrefix={arXiv},
      primaryClass={cs.DS}
}
```
