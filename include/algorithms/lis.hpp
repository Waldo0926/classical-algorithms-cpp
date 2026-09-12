#pragma once
#include <vector>

namespace algorithms {
struct LisResult {
    int length{};
    std::vector<int> sequence;
};

LisResult longest_increasing_subsequence(const std::vector<int>& values);
}
