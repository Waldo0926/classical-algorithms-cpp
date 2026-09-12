#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

namespace algorithms {
struct Item {
    int weight{};
    int value{};
};

struct KnapsackResult {
    int value{};
    int weight{};
    std::vector<int> selected_indices;
    std::uint64_t nodes_visited{};
    std::uint64_t nodes_pruned{};
};

KnapsackResult knapsack_backtracking(const std::vector<Item>& items, int capacity);
KnapsackResult knapsack_branch_and_bound(const std::vector<Item>& items, int capacity);

struct GeneticConfig {
    std::size_t population_size{120};
    std::size_t generations{250};
    double mutation_rate{0.03};
    std::size_t elite_count{8};
    unsigned seed{42};
};
KnapsackResult knapsack_genetic(const std::vector<Item>& items, int capacity,
                                const GeneticConfig& config = {});
}
