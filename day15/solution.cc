#include "day15/solution.h"

#include <bitset>
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

int64_t GameState(const std::vector<int>& entries, int max_iterations) {
  absl::flat_hash_map<int, int> history;

  int iteration = 1;
  int last_number;
  for (const auto& spoken_number : entries) {
    history[spoken_number] = iteration++;
    last_number = spoken_number;
    std::cout << "iteration " << iteration - 1 << " => number " << last_number
              << std::endl;
  }
  history.erase(last_number);
  --iteration;
  int one_before = last_number;

  while (true) {
    if (!history.contains(one_before)) {
      last_number = 0;
    } else {
      auto& latest_mention = history[one_before];
      last_number = iteration - latest_mention;
    }
    history[one_before] = iteration;

    if (iteration == max_iterations) {
      return one_before;
    }
    ++iteration;

    one_before = last_number;
  }

  return 1;
}

}  // namespace

absl::StatusOr<int64_t> Numbers(const std::vector<int>& entries, bool second) {
  if (!second) {
    return GameState(entries, 2020);
  }
  return GameState(entries, 30000000);
}

