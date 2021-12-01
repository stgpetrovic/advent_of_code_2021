#include "day09/solution.h"

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

namespace {

int64_t FirstNotSumming(const std::vector<std::string>& entries, int preamble) {
  absl::flat_hash_map<int64_t, int64_t> sums;
  std::vector<absl::flat_hash_set<int64_t>> oldest(entries.size());

  for (int i = 0; i < preamble - 1; ++i) {
    for (int j = 1; j < preamble; ++j) {
      int a, b;
      CHECK(absl::SimpleAtoi(entries[i], &a));
      CHECK(absl::SimpleAtoi(entries[j], &b));
      if (!sums.contains(a + b)) {
        sums.insert({a + b, 0});
      }
      ++sums[a + b];
      oldest[i].insert(a + b);
    }
  }

  for (int i = preamble; i < entries.size(); ++i) {
    int a;
    CHECK(absl::SimpleAtoi(entries[i], &a));
    if (!sums.contains(a)) {
      return a;
    }
    for (const auto& old : oldest[i - preamble]) {
      if (sums[old] > 0) {
        --sums[old];
      }
    }
    for (int j = i - preamble + 1; j < i; ++j) {
      int b;
      CHECK(absl::SimpleAtoi(entries[j], &b));
      if (!sums.contains(a + b)) {
        sums.insert({a + b, 0});
      }
      ++sums[a + b];
      oldest[i].insert(a + b);
    }
  }
  return -1;
}

absl::StatusOr<int64_t> Sum(const std::vector<std::string>& entries, int len,
                            int64_t want) {
  std::vector<int64_t> n;
  absl::c_transform(entries, std::back_inserter(n), [](const std::string& e) {
    int64_t a;
    CHECK(absl::SimpleAtoi(e, &a));
    return a;
  });
  int64_t sum = 0;
  for (int i = 0; i < n.size(); ++i) {
    if (i < len) {
      sum += n[i];
      continue;
    }
    if (sum == want) {
      int64_t min = 1000000000, max = 0;
      for (int j = i - len; j < i; ++j) {
        min = std::min(min, n[j]);
        max = std::max(max, n[j]);
      }
      return min + max;
    }
    sum += n[i];
    sum -= n[i - len];
  }
  return absl::InvalidArgumentError("neznam");
}

}  // namespace

absl::StatusOr<int64_t> Count(const std::vector<std::string>& entries,
                              int preamble, bool second) {
  auto n = FirstNotSumming(entries, preamble);
  // First.
  if (!second) {
    return n;
  }

  // Second.
  for (int i = 2; i < entries.size(); ++i) {
    auto sum = Sum(entries, i, n);
    if (sum.ok()) {
      return *sum;
    }
  }
  return absl::InvalidArgumentError("no solution");
}

