#pragma once
#include <vector>

namespace algorithms {
struct CliqueResult {
    std::vector<int> vertices;
    unsigned long long nodes_visited{};
    unsigned long long nodes_pruned{};
};

CliqueResult maximum_clique(const std::vector<std::vector<int>>& adjacency);
}
