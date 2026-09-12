# C++ 经典算法设计与分析

这是一个面向 GitHub Portfolio 展示的 C++17 算法项目，由本科《算法设计与分析》课程作业重新整理、修复和工程化而成。

本仓库不是把原始作业文件直接上传，而是保留其中有价值的算法主题，统一重构为可编译、可测试、可复现实验的代码库。

## 包含的算法

| 问题 | 算法范式 | 是否保证最优 | 复杂度 / 特点 |
|---|---|---:|---|
| 最长递增子序列 LIS | 动态规划 | 是 | `O(n^2)` |
| 逆序对统计 | 分治 / 归并排序 | 是 | `O(n log n)` |
| 0-1 背包 | 回溯 | 是 | 最坏 `O(2^n)` |
| 0-1 背包 | 分支限界 / 上界剪枝 | 是 | 最坏仍为指数级，但可以减少搜索节点 |
| 0-1 背包 | 遗传算法 | 否 | 随机启发式近似搜索 |
| 最大团 | 分支限界 | 是 | 最坏指数级 |

## 项目的重点

0-1 背包问题同时实现了三种不同方法：

1. **回溯法**：完整搜索解空间，保证最优解；
2. **分支限界法**：使用分数背包上界进行剪枝，在保持精确性的同时减少搜索；
3. **遗传算法**：通过种群、交叉、变异和精英保留进行启发式搜索，不保证每次得到全局最优解。

因此，这个项目不仅展示“会写算法”，还可以用于解释精确算法与启发式算法、搜索空间、剪枝策略和性能之间的取舍。

## 编译运行

需要 C++17 编译器和 CMake 3.16+：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/algorithm_demo
```

## 自动测试

```bash
ctest --test-dir build --output-on-failure
```

测试包含 LIS、逆序对、0-1 背包和最大团的已知案例，并验证分支限界背包与完整回溯法得到相同最优值。

## Benchmark

```bash
./build/algorithm_benchmark > benchmark-results.csv
```

会输出三种背包算法的解价值、重量、搜索节点数、剪枝数和运行时间，便于比较。

## 目录结构

```text
.
├── apps/                 # 示例程序
├── benchmarks/           # 背包算法对比实验
├── docs/                 # 算法分析与课程作业重构说明
├── include/algorithms/   # 头文件 / 接口
├── src/                  # 算法实现
├── tests/                # 正确性测试
├── .github/workflows/    # GitHub Actions CI
└── CMakeLists.txt
```

## 关于原课程作业

原始作业压缩包中包含多个实验版本、`.exe`、Word 报告、截图以及姓名/学号等个人信息，因此没有直接放入公开仓库。核心算法思想已经重新整理到 [`docs/algorithm-notes.md`](docs/algorithm-notes.md)，可复现实验结果见 [`docs/benchmark-results.md`](docs/benchmark-results.md)，重构说明见 [`docs/coursework-origin.md`](docs/coursework-origin.md)。

## 相关项目

另一个独立仓库 [**N-Queens Algorithm Visualizer**](https://github.com/Waldo0926/n-queens-algorithm-visualizer) 专门展示 N 皇后问题中的回溯、状态空间剪枝和爬山算法，并提供可视化演示。两个仓库共同构成算法方向的 Portfolio 展示。
