#include "algorithms/knapsack.hpp"
#include <algorithm>
#include <numeric>

namespace algorithms {
namespace {
void exhaustive_dfs(const std::vector<Item>& items, int capacity, int index,
                    int current_weight, int current_value, std::vector<int>& chosen,
                    KnapsackResult& best) {
    ++best.nodes_visited;
    if (index == static_cast<int>(items.size())) {
        if (current_value > best.value) {
            best.value = current_value;
            best.weight = current_weight;
            best.selected_indices = chosen;
        }
        return;
    }

    if (current_weight + items[index].weight <= capacity) {
        chosen.push_back(index);
        exhaustive_dfs(items, capacity, index + 1,
                       current_weight + items[index].weight,
                       current_value + items[index].value, chosen, best);
        chosen.pop_back();
    }
    exhaustive_dfs(items, capacity, index + 1, current_weight, current_value, chosen, best);
}

struct IndexedItem { Item item; int original_index; double density; };

double fractional_bound(const std::vector<IndexedItem>& items, int index,
                        int capacity, int current_weight, int current_value) {
    int remaining = capacity - current_weight;
    double bound = current_value;
    for (int i = index; i < static_cast<int>(items.size()) && remaining > 0; ++i) {
        if (items[i].item.weight <= remaining) {
            remaining -= items[i].item.weight;
            bound += items[i].item.value;
        } else {
            bound += items[i].density * remaining;
            break;
        }
    }
    return bound;
}

void bounded_dfs(const std::vector<IndexedItem>& items, int capacity, int index,
                 int current_weight, int current_value, std::vector<int>& chosen,
                 KnapsackResult& best) {
    ++best.nodes_visited;
    if (current_value > best.value) {
        best.value = current_value;
        best.weight = current_weight;
        best.selected_indices = chosen;
    }
    if (index == static_cast<int>(items.size())) return;

    if (fractional_bound(items, index, capacity, current_weight, current_value) <= best.value) {
        ++best.nodes_pruned;
        return;
    }

    const auto& entry = items[index];
    if (current_weight + entry.item.weight <= capacity) {
        chosen.push_back(entry.original_index);
        bounded_dfs(items, capacity, index + 1,
                    current_weight + entry.item.weight,
                    current_value + entry.item.value, chosen, best);
        chosen.pop_back();
    }
    bounded_dfs(items, capacity, index + 1, current_weight, current_value, chosen, best);
}
}

KnapsackResult knapsack_backtracking(const std::vector<Item>& items, int capacity) {
    KnapsackResult best;
    std::vector<int> chosen;
    exhaustive_dfs(items, capacity, 0, 0, 0, chosen, best);
    return best;
}

KnapsackResult knapsack_branch_and_bound(const std::vector<Item>& items, int capacity) {
    std::vector<IndexedItem> sorted;
    sorted.reserve(items.size());
    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        const double density = items[i].weight == 0 ? 0.0
            : static_cast<double>(items[i].value) / items[i].weight;
        sorted.push_back({items[i], i, density});
    }
    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
        return a.density > b.density;
    });

    KnapsackResult best;
    std::vector<int> chosen;
    bounded_dfs(sorted, capacity, 0, 0, 0, chosen, best);
    std::sort(best.selected_indices.begin(), best.selected_indices.end());
    return best;
}
}
