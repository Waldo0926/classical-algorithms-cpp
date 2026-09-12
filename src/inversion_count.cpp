#include "algorithms/inversion_count.hpp"

namespace algorithms {
namespace {
std::int64_t merge_count(std::vector<int>& a, std::vector<int>& tmp, int left, int right) {
    if (right - left <= 1) return 0;
    const int mid = left + (right - left) / 2;
    std::int64_t total = merge_count(a, tmp, left, mid) + merge_count(a, tmp, mid, right);
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            total += mid - i;
        }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < right) tmp[k++] = a[j++];
    for (int x = left; x < right; ++x) a[x] = tmp[x];
    return total;
}
}

std::int64_t count_inversions(std::vector<int> values) {
    std::vector<int> tmp(values.size());
    return merge_count(values, tmp, 0, static_cast<int>(values.size()));
}
}
