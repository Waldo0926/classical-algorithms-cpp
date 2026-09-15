# Classical Algorithms in C++

[![Type](https://img.shields.io/badge/Type-Coursework-2563eb?style=for-the-badge)](#)
[![Tech](https://img.shields.io/badge/Tech-C%2B%2B17-7c3aed?style=for-the-badge)](#)


A portfolio-oriented C++17 implementation of classical algorithm-design techniques, reconstructed from undergraduate **Algorithm Design and Analysis** coursework and refactored into a tested, reproducible codebase.

[中文说明](README.zh-CN.md)

## What this repository demonstrates

Instead of publishing raw coursework files, this repository focuses on reusable implementations, correctness tests, complexity analysis, search statistics, and direct comparison between exact and heuristic approaches.

| Problem | Technique | Exact? | Complexity / characteristic |
|---|---|---:|---|
| Longest Increasing Subsequence | Dynamic Programming | Yes | `O(n^2)` |
| Inversion Count | Divide & Conquer / Merge Sort | Yes | `O(n log n)` |
| 0-1 Knapsack | Backtracking | Yes | `O(2^n)` worst case |
| 0-1 Knapsack | Branch and Bound | Yes | Exponential worst case; prunes using a fractional upper bound |
| 0-1 Knapsack | Genetic Algorithm | No | Heuristic; population × generations |
| Maximum Clique | Branch and Bound | Yes | Exponential worst case |

## Why the Knapsack comparison is useful

The same combinatorial optimization problem is solved in three different ways:

1. **Backtracking** explores the exact decision tree.
2. **Branch and Bound** remains exact but skips subtrees whose optimistic bound cannot beat the incumbent.
3. **Genetic Algorithm** trades the guarantee of optimality for heuristic search.

This makes the project useful for discussing not only implementation, but also trade-offs between completeness, pruning, randomness, and runtime.

## Build and run

Requirements: a C++17 compiler and CMake 3.16+.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/algorithm_demo
```

On Windows, the executable may be under `build/Release/` depending on the generator.

## Run tests

```bash
ctest --test-dir build --output-on-failure
```

The tests cover known LIS, inversion-count, 0-1 Knapsack, and Maximum Clique cases, and verify that the bounded Knapsack solver returns the same optimum as exhaustive backtracking.

## Run the benchmark

```bash
./build/algorithm_benchmark > benchmark-results.csv
```

The benchmark reports solution value, solution weight, search nodes, pruned nodes, and runtime for the three Knapsack approaches on deterministic generated instances.

Example CSV schema:

```text
n,algorithm,value,weight,nodes,pruned,time_ms
```

## Project structure

```text
.
├── apps/                 # Demonstration executable
├── benchmarks/           # Reproducible Knapsack comparison
├── docs/                 # Algorithm analysis and refactoring notes
├── include/algorithms/   # Public algorithm interfaces
├── src/                  # Implementations
├── tests/                # Correctness tests
├── .github/workflows/    # CI build and test
└── CMakeLists.txt
```

## Design notes

Detailed algorithm explanations are in [`docs/algorithm-notes.md`](docs/algorithm-notes.md). A reproducible benchmark snapshot is in [`docs/benchmark-results.md`](docs/benchmark-results.md). The relationship between this repository and the original coursework is documented in [`docs/coursework-origin.md`](docs/coursework-origin.md).

## Related project

For a visual treatment of state-space search, see my [**N-Queens Algorithm Visualizer**](https://github.com/Waldo0926/n-queens-algorithm-visualizer), which compares backtracking, pruned state-space search, and hill climbing on the N-Queens problem.
