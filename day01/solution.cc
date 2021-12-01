#include "day01/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <limits>
#include <vector>

int32_t CountIncreases(const std::vector<int32_t>& numbers) {
  int32_t increases = 0;
  int32_t previous_depth = std::numeric_limits<int32_t>::max();
  for (const auto& depth : numbers) {
    if (depth > previous_depth) {
      ++increases;
    }
    previous_depth = depth;
  }
  return increases;
}

int32_t CountWindowIncreases(const std::vector<int32_t>& numbers) {
  int32_t increases = 0, sum = 0;
  std::vector<int32_t> prefix_sums{0};
  for (const auto& depth : numbers) {
    sum += depth;
    prefix_sums.push_back(sum);
  }
  for (size_t i = 3; i < prefix_sums.size(); ++i) {
    if (prefix_sums[i] - prefix_sums[i - 3] <
        prefix_sums[i + 1] - prefix_sums[i - 2]) {
      ++increases;
    }
  }
  return increases;
}
