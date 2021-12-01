#include "day03/solution.h"

#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"

MutatedForest::MutatedForest(const std::vector<std::string>& entries) {
  for (int i = 0; i < entries.size(); ++i) {
    for (int j = 0; j < entries[i].length(); ++j) {
      if (entries[i][j] == '#') {
        trees_.insert({i, j});
      }
    }
  }
  width_ = entries[0].length();
}

bool MutatedForest::IsTree(size_t i, size_t j) const {
  return trees_.contains({i, j % width_});
}

absl::StatusOr<int64_t> CountTrees(const std::vector<std::string>& entries,
                                   const std::vector<Point>& slopes) {
  MutatedForest mf(entries);

  int64_t total_multiplier = 1;
  for (const auto& slope : slopes) {
    int total_trees = 0;
    for (int i = 0; i < entries.size(); ++i) {
      if (mf.IsTree(i * slope.first, i * slope.second)) {
        ++total_trees;
      }
    }
    total_multiplier *= total_trees;
  }

  return total_multiplier;
}

