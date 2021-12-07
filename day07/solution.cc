#include "day07/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

namespace {

constexpr int64_t kMax = 2000;

int64_t SumFirst(int n) { return n * (n + 1) / 2; }

std::vector<int64_t> VectorAtoi(const std::vector<std::string>& in) {
  std::vector<int64_t> i;
  for (const auto& s : in) {
    int64_t n;
    CHECK(absl::SimpleAtoi(s, &n));
    i.push_back(n);
  }
  return i;
}

}  // namespace

absl::StatusOr<int64_t> Crevetten(const std::vector<std::string>& input,
                                  bool acc) {
  std::vector<int64_t> crabs = VectorAtoi(absl::StrSplit(input[0], ","));
  absl::flat_hash_map<std::pair<short, short>, int64_t> D;
  int64_t cnts[kMax] = {};
  for (const auto& skamp : crabs) {
    ++cnts[skamp];
    for (int i = 0; i < kMax; ++i) {
      int32_t d = std::abs(skamp - i);
      D.insert({{skamp, i}, acc ? SumFirst(d) : d});
    }
  }

  std::pair<int64_t, size_t> min_col{std::numeric_limits<int64_t>::max(), 0};
  for (int j = 0; j < kMax; ++j) {
    uint64_t min = 0;
    for (int i = 0; i < kMax; ++i) {
      if (D.contains({i, j})) {
        min += cnts[i] * D.at({i, j});
      }
    }
    if (min < min_col.first) {
      min_col = {min, j};
    }
  }
  return min_col.first;
}
