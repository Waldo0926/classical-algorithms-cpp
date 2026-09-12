#include "algorithms/knapsack.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

using Clock = std::chrono::steady_clock;

template <class F>
auto timed(F&& f) {
    const auto start = Clock::now();
    auto result = f();
    const auto stop = Clock::now();
    const double ms = std::chrono::duration<double, std::milli>(stop - start).count();
    return std::pair{result, ms};
}

int main() {
    using namespace algorithms;
    std::mt19937 rng(2026);
    std::uniform_int_distribution<int> weight(2, 25), value(5, 60);

    std::cout << "n,algorithm,value,weight,nodes,pruned,time_ms\n";
    for (int n : {12, 16, 20}) {
        std::vector<Item> items;
        int sum_weight = 0;
        for (int i = 0; i < n; ++i) {
            items.push_back({weight(rng), value(rng)});
            sum_weight += items.back().weight;
        }
        const int capacity = sum_weight * 40 / 100;

        auto [back, back_ms] = timed([&]{ return knapsack_backtracking(items, capacity); });
        auto [bnb, bnb_ms] = timed([&]{ return knapsack_branch_and_bound(items, capacity); });
        GeneticConfig cfg; cfg.seed = 2026 + n;
        auto [ga, ga_ms] = timed([&]{ return knapsack_genetic(items, capacity, cfg); });

        auto print = [&](const char* name, const KnapsackResult& r, double ms) {
            std::cout << n << ',' << name << ',' << r.value << ',' << r.weight << ','
                      << r.nodes_visited << ',' << r.nodes_pruned << ','
                      << std::fixed << std::setprecision(3) << ms << '\n';
        };
        print("backtracking", back, back_ms);
        print("branch_and_bound", bnb, bnb_ms);
        print("genetic", ga, ga_ms);
    }
}
