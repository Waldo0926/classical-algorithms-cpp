# Algorithm Notes

This project reconstructs several assignments from an undergraduate **Algorithm Design and Analysis** course into a consistent, testable C++17 codebase.

## 1. Longest Increasing Subsequence — Dynamic Programming

For each position `i`, define `dp[i]` as the length of the longest strictly increasing subsequence ending at `i`.

```text
dp[i] = 1 + max(dp[j]) for every j < i with a[j] < a[i]
```

The implementation also stores a predecessor index so one valid optimal subsequence can be reconstructed.

- Time: `O(n^2)`
- Space: `O(n)`

## 2. Inversion Count — Divide and Conquer

A pair `(i, j)` is an inversion when `i < j` but `a[i] > a[j]`. During merge sort, whenever an element from the right half is placed before an unmerged element from the left half, all remaining left-half elements form inversions with it.

- Time: `O(n log n)`
- Space: `O(n)`

The coursework version contained a merge-step pointer bug; this portfolio version corrects it and adds regression tests.

## 3. 0-1 Knapsack — Exhaustive Backtracking

Each item creates two branches: include or exclude. In the worst case this explores the full binary decision tree.

- Exact: yes
- Worst-case time: `O(2^n)`
- Search statistic: nodes visited

## 4. 0-1 Knapsack — Branch and Bound

Items are ordered by value density. At each search node, a fractional-knapsack relaxation estimates an optimistic upper bound for the best value still reachable. If that bound cannot beat the incumbent solution, the subtree is pruned.

- Exact: yes
- Worst-case time: exponential
- Practical improvement: fewer explored nodes when the bound is informative

## 5. 0-1 Knapsack — Genetic Algorithm

A chromosome is a binary vector indicating selected items. The implementation uses:

- random population initialization;
- fitness equal to total value for feasible solutions;
- elitism;
- one-point crossover;
- bit mutation;
- deterministic seeds for reproducible experiments.

This is a heuristic method and **does not guarantee the global optimum**.

## 6. Maximum Clique — Branch and Bound

The search incrementally constructs a clique. Candidate vertices are filtered to those adjacent to every vertex already selected. If `current_size + candidates_remaining` cannot exceed the incumbent clique size, the branch is pruned.

- Exact: yes
- Worst-case time: exponential
- Search statistics: nodes visited and branches pruned
