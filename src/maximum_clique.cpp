#include "algorithms/maximum_clique.hpp"
#include <algorithm>

namespace algorithms {
namespace {
void search(const std::vector<std::vector<int>>& graph, std::vector<int>& current,
            std::vector<int> candidates, CliqueResult& best) {
    ++best.nodes_visited;
    if (current.size() + candidates.size() <= best.vertices.size()) {
        ++best.nodes_pruned;
        return;
    }
    if (candidates.empty()) {
        if (current.size() > best.vertices.size()) best.vertices = current;
        return;
    }

    while (!candidates.empty()) {
        if (current.size() + candidates.size() <= best.vertices.size()) {
            ++best.nodes_pruned;
            return;
        }
        const int v = candidates.back();
        candidates.pop_back();
        current.push_back(v);

        std::vector<int> next;
        for (int u : candidates) if (graph[v][u]) next.push_back(u);
        if (current.size() > best.vertices.size()) best.vertices = current;
        search(graph, current, std::move(next), best);
        current.pop_back();
    }
}
}

CliqueResult maximum_clique(const std::vector<std::vector<int>>& adjacency) {
    const int n = static_cast<int>(adjacency.size());
    for (const auto& row : adjacency) {
        if (static_cast<int>(row.size()) != n) return {};
    }
    std::vector<int> candidates(n);
    for (int i = 0; i < n; ++i) candidates[i] = i;
    std::vector<int> current;
    CliqueResult best;
    search(adjacency, current, std::move(candidates), best);
    std::sort(best.vertices.begin(), best.vertices.end());
    return best;
}
}
