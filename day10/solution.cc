#include "day10/solution.h"

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
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

namespace {

int64_t CountJolts(const std::set<int64_t>& jolts) {
  int64_t three = 0, one = 0;
  int64_t acc = 0;
  for (const auto& jolt : jolts) {
    if (jolt - acc > 3) {
      return -1;
    }
    if (jolt - acc == 1) {
      ++one;
    } else if (jolt - acc == 3) {
      ++three;
    }
    acc = jolt;
  }
  return three * one;
}

int64_t Compositions(const std::set<int64_t>& jolts, int n) {
  static auto* cache = new absl::flat_hash_map<int, int64_t>;

  bool hasOne = jolts.find(n - 1) != jolts.end();
  bool hasTwo = jolts.find(n - 2) != jolts.end();
  bool hasThree = jolts.find(n - 3) != jolts.end();

  if (n == 0) {
    return 1;
  }
  if (cache->contains(n)) {
    return cache->at(n);
  }

  int64_t ret = (hasOne ? Compositions(jolts, n - 1) : 0) +
                (hasTwo ? Compositions(jolts, n - 2) : 0) +
                (hasThree ? Compositions(jolts, n - 3) : 0);
  cache->insert({n, ret});
  return ret;
}

}  // namespace

absl::StatusOr<int64_t> Jolt(const std::vector<std::string>& entries,
                             bool second) {
  std::set<int64_t> jolts;
  absl::c_transform(entries, std::inserter(jolts, jolts.end()),
                    [](const std::string& in) {
                      int64_t a;
                      CHECK(absl::SimpleAtoi(in, &a));
                      return a;
                    });
  jolts.insert(*absl::c_max_element(jolts) + 3);  // device

  // First.
  if (!second) {
    return CountJolts(jolts);
  }
  jolts.insert(0);
  int max = *absl::c_max_element(jolts) + 3;
  jolts.erase(*absl::c_max_element(jolts) + 3);  // device
  std::cout << absl::StrJoin(jolts, ", ") << std::endl;
  return Compositions(jolts, max);

  // Second.
  return absl::InvalidArgumentError("no code version terminates.");
}

