#include "algorithms/inversion_count.hpp"
#include "algorithms/knapsack.hpp"
#include "algorithms/lis.hpp"
#include "algorithms/maximum_clique.hpp"
#include <iostream>

int main() {
    using namespace algorithms;

    const std::vector<int> sequence{5, 6, 7, 1, 2, 8};
    const auto lis = longest_increasing_subsequence(sequence);
    std::cout << "LIS length: " << lis.length << " | sequence:";
    for (int x : lis.sequence) std::cout << ' ' << x;
    std::cout << "\n";

    std::cout << "Inversions in [2, 4, 1, 3, 5]: "
              << count_inversions({2, 4, 1, 3, 5}) << "\n";

    const std::vector<Item> items{{10,15},{15,25},{20,30},{25,50},{30,55},{35,75}};
    constexpr int capacity = 80;
    const auto exact = knapsack_branch_and_bound(items, capacity);
    const auto genetic = knapsack_genetic(items, capacity);
    std::cout << "Knapsack exact value: " << exact.value << " | selected:";
    for (int i : exact.selected_indices) std::cout << ' ' << (i + 1);
    std::cout << "\nKnapsack genetic value: " << genetic.value << " | selected:";
    for (int i : genetic.selected_indices) std::cout << ' ' << (i + 1);
    std::cout << "\n";

    const std::vector<std::vector<int>> graph{
        {0,1,1,0,0},
        {1,0,1,1,0},
        {1,1,0,1,0},
        {0,1,1,0,1},
        {0,0,0,1,0}
    };
    const auto clique = maximum_clique(graph);
    std::cout << "Maximum clique size: " << clique.vertices.size() << " | vertices:";
    for (int v : clique.vertices) std::cout << ' ' << (v + 1);
    std::cout << "\n";
}
