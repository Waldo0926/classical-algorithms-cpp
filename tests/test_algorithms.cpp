#include "algorithms/inversion_count.hpp"
#include "algorithms/knapsack.hpp"
#include "algorithms/lis.hpp"
#include "algorithms/maximum_clique.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}
}

int main() {
    using namespace algorithms;
    try {
        {
            auto r = longest_increasing_subsequence({5,6,7,1,2,8});
            require(r.length == 4, "LIS length should be 4");
            require(r.sequence.size() == 4, "LIS reconstruction should contain 4 values");
            for (std::size_t i = 1; i < r.sequence.size(); ++i)
                require(r.sequence[i-1] < r.sequence[i], "LIS reconstruction must be strictly increasing");
        }

        require(count_inversions({2,4,1,3,5}) == 3, "Inversion count should be 3");
        require(count_inversions({5,4,3,2,1}) == 10, "Reverse length-5 array should have 10 inversions");
        require(count_inversions({1,2,3,4}) == 0, "Sorted array should have zero inversions");

        const std::vector<Item> items{{10,15},{15,25},{20,30},{25,50},{30,55},{35,75}};
        const int capacity = 80;
        const auto brute = knapsack_backtracking(items, capacity);
        const auto bounded = knapsack_branch_and_bound(items, capacity);
        require(brute.value == 155, "Known knapsack optimum should be 155");
        require(bounded.value == brute.value, "Branch and bound must match exhaustive backtracking");
        require(bounded.weight <= capacity, "Branch-and-bound result must be feasible");
        require(bounded.nodes_visited <= brute.nodes_visited,
                "Branch and bound should not visit more nodes on the coursework instance");

        GeneticConfig cfg;
        cfg.seed = 42;
        cfg.population_size = 200;
        cfg.generations = 300;
        cfg.mutation_rate = 0.04;
        auto ga = knapsack_genetic(items, capacity, cfg);
        require(ga.weight <= capacity, "Genetic result must be feasible");
        require(ga.value >= 130, "Seeded genetic run should reach a strong feasible solution");

        const std::vector<std::vector<int>> graph{
            {0,1,1,0,0},
            {1,0,1,1,0},
            {1,1,0,1,0},
            {0,1,1,0,1},
            {0,0,0,1,0}
        };
        auto clique = maximum_clique(graph);
        require(clique.vertices.size() == 3, "Known graph should have maximum clique size 3");

        std::cout << "All tests passed.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failure: " << e.what() << '\n';
        return 1;
    }
}
