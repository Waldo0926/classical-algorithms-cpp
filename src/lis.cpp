#include "algorithms/lis.hpp"
#include <algorithm>

namespace algorithms {
LisResult longest_increasing_subsequence(const std::vector<int>& values) {
    if (values.empty()) return {};

    const int n = static_cast<int>(values.size());
    std::vector<int> dp(n, 1);
    std::vector<int> parent(n, -1);
    int best_end = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (values[j] < values[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > dp[best_end]) best_end = i;
    }

    std::vector<int> sequence;
    for (int i = best_end; i != -1; i = parent[i]) sequence.push_back(values[i]);
    std::reverse(sequence.begin(), sequence.end());
    return {dp[best_end], sequence};
}
}
