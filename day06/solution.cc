#include "day06/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

namespace {

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

// TODO: mozda nesto sa 2^(days/7+1) +- dronjci pocetni.
absl::StatusOr<int64_t> Spawn(const std::vector<std::string>& input,
                                  int64_t total_days) {
  LOG(INFO) << " Ages " << input[0];
  std::vector<int64_t> ages = VectorAtoi(absl::StrSplit(input[0], ","));
  int64_t clock[9] = {};
  for (const auto& age : ages) {
    ++clock[age];
  }

  int64_t day = 0;
  while (day++ != total_days) {
    int64_t new_fish = clock[0];
    clock[0] = 0;
    for (size_t age = 1; age < 9; ++age) {
      clock[age - 1] += clock[age];
      clock[age] = 0;
    }
    if (new_fish > 0) {
      clock[6] += new_fish;
      clock[8] += new_fish;
    }
  }

  int64_t sum=0;
  for (size_t age = 0; age < 9; ++age) {
    sum += clock[age];
    LOG(INFO) << sum;
  }

  return sum;
}
