# Benchmark Snapshot

The benchmark uses deterministic pseudo-random 0-1 Knapsack instances (`seed = 2026`) so runs are reproducible. Values below are a snapshot from a Linux Release build and are intended to illustrate search behavior; absolute runtime depends on hardware and compiler.

| Items | Algorithm | Best value | Weight | Nodes / evaluations | Pruned | Time (ms) |
|---:|---|---:|---:|---:|---:|---:|
| 12 | Backtracking | 298 | 64 | 2,906 | 0 | 0.016 |
| 12 | Branch and Bound | 298 | 64 | 45 | 9 | 0.002 |
| 12 | Genetic Algorithm | 298 | 64 | 30,120 | — | 6.728 |
| 16 | Backtracking | 364 | 72 | 39,849 | 0 | 0.129 |
| 16 | Branch and Bound | 364 | 72 | 35 | 12 | 0.003 |
| 16 | Genetic Algorithm | 364 | 72 | 30,120 | — | 7.974 |
| 20 | Backtracking | 424 | 102 | 608,246 | 0 | 1.732 |
| 20 | Branch and Bound | 424 | 102 | 31 | 10 | 0.003 |
| 20 | Genetic Algorithm | 424 | 102 | 30,120 | — | 11.217 |

## Interpretation

For these instances, the fractional upper bound is highly informative: branch and bound reaches the same exact optimum as exhaustive backtracking while visiting far fewer search nodes. The genetic algorithm also reaches the optimum in this deterministic snapshot, but it remains a heuristic method and does not provide an optimality guarantee in general.

Run the benchmark yourself with:

```bash
./build/algorithm_benchmark > benchmark-results.csv
```
