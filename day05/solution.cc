#include "day05/solution.h"

#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

absl::StatusOr<int64_t> SeatId(const std::vector<std::string>& entries,
                               bool second) {
  int max = -1;
  int missing;
  absl::flat_hash_set<int16_t> seen;
  for (const auto& entry : entries) {
    int row = std::stoi(
        absl::StrReplaceAll(entry, {{"F", "0"}, {"B", "1"}}).substr(0, 7),
        nullptr, 2);
    int column = std::stoi(
        absl::StrReplaceAll(entry.substr(7), {{"L", "0"}, {"R", "1"}}), nullptr,
        2);
    seen.insert(row * 8 + column);
    max = std::max(max, row * 8 + column);
  }
  if (second) {
    for (int i = 0; i < 911; ++i) {
      if (!seen.contains(i) && i > 100) {
        missing = i;
      }
    }
    return missing;
  }
  if (max == -1) {
    return absl::InvalidArgumentError("error");
  }
  return max;
}

