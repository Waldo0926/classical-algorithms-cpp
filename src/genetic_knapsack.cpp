#include "algorithms/knapsack.hpp"
#include <algorithm>
#include <random>

namespace algorithms {
namespace {
struct Chromosome {
    std::vector<unsigned char> bits;
    int fitness{};
    int weight{};
};

void evaluate(Chromosome& c, const std::vector<Item>& items, int capacity) {
    c.weight = 0;
    c.fitness = 0;
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (c.bits[i]) {
            c.weight += items[i].weight;
            c.fitness += items[i].value;
        }
    }
    if (c.weight > capacity) c.fitness = 0;
}
}

KnapsackResult knapsack_genetic(const std::vector<Item>& items, int capacity,
                                const GeneticConfig& config) {
    if (items.empty() || config.population_size == 0) return {};
    std::mt19937 rng(config.seed);
    std::bernoulli_distribution initial_bit(0.5);
    std::bernoulli_distribution mutate(config.mutation_rate);

    std::vector<Chromosome> population(config.population_size);
    for (auto& c : population) {
        c.bits.resize(items.size());
        for (auto& bit : c.bits) bit = static_cast<unsigned char>(initial_bit(rng));
        evaluate(c, items, capacity);
    }

    auto better = [](const Chromosome& a, const Chromosome& b) { return a.fitness > b.fitness; };
    Chromosome best = *std::max_element(population.begin(), population.end(),
        [&](const auto& a, const auto& b){ return a.fitness < b.fitness; });

    const std::size_t elite = std::min(config.elite_count, config.population_size);
    std::uniform_int_distribution<std::size_t> parent_dist(0, std::max<std::size_t>(1, config.population_size / 2) - 1);

    for (std::size_t gen = 0; gen < config.generations; ++gen) {
        std::sort(population.begin(), population.end(), better);
        if (population.front().fitness > best.fitness) best = population.front();

        std::vector<Chromosome> next;
        next.reserve(config.population_size);
        for (std::size_t i = 0; i < elite; ++i) next.push_back(population[i]);

        while (next.size() < config.population_size) {
            const auto& p1 = population[parent_dist(rng)];
            const auto& p2 = population[parent_dist(rng)];
            Chromosome child;
            child.bits.resize(items.size());
            const std::size_t cut = items.size() <= 1 ? items.size() : std::uniform_int_distribution<std::size_t>(1, items.size() - 1)(rng);
            for (std::size_t i = 0; i < items.size(); ++i) {
                child.bits[i] = i < cut ? p1.bits[i] : p2.bits[i];
                if (mutate(rng)) child.bits[i] = static_cast<unsigned char>(!child.bits[i]);
            }
            evaluate(child, items, capacity);
            next.push_back(std::move(child));
        }
        population.swap(next);
    }

    std::sort(population.begin(), population.end(), better);
    if (population.front().fitness > best.fitness) best = population.front();

    KnapsackResult result;
    result.value = best.fitness;
    result.weight = best.weight;
    result.nodes_visited = config.population_size * (config.generations + 1);
    for (std::size_t i = 0; i < best.bits.size(); ++i) if (best.bits[i]) result.selected_indices.push_back(static_cast<int>(i));
    return result;
}
}
