# Coursework Origin and Refactoring Notes

This repository is a cleaned and re-engineered version of algorithms originally implemented for an undergraduate **Algorithm Design and Analysis** course.

The original submission archive contained multiple experimental versions, compiled `.exe` files, Chinese-language Word reports, screenshots, local-development artifacts, and personally identifying information. Those raw submission files are intentionally **not included** in this public portfolio repository.

## What was preserved

The portfolio version preserves the core topics and algorithmic ideas from the coursework:

- `O(n^2)` dynamic programming for Longest Increasing Subsequence;
- exhaustive backtracking for 0-1 Knapsack;
- upper-bound pruning for 0-1 Knapsack;
- branch-and-bound search for Maximum Clique;
- merge-sort-based inversion counting;
- a Genetic Algorithm approximation for 0-1 Knapsack.

## What was improved

- corrected known bugs in legacy implementations;
- replaced fixed-size global arrays with standard C++ containers;
- separated algorithms into reusable modules;
- standardized indexing and return types;
- added solution reconstruction where useful;
- made stochastic experiments reproducible with explicit random seeds;
- added CMake, automated tests, benchmarking, and GitHub Actions CI;
- removed student ID, local paths, binaries, IDE files, and duplicated drafts.

This makes the repository suitable for public review while keeping a transparent link to its educational origin.
