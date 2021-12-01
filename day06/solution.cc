#include "day06/solution.h"

#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_map.h"
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

namespace {

int16_t CountUniqueAnswers(const std::vector<std::string>& answers) {
  int sum = 0;

  absl::flat_hash_set<char> acc;
  for (const auto& row : answers) {
    if (row.empty()) {
      sum += acc.size();
      acc.clear();
    }
    acc.insert(row.begin(), row.end());
  }
  sum += acc.size();
  return sum;
}

int16_t CountUniqueAnswersAll(const std::vector<std::string>& answers) {
  int sum = 0;

  absl::flat_hash_map<char, int16_t> acc;
  int people = 0;
  for (const auto& row : answers) {
    if (row.empty()) {
      for (const auto& [c, cnt] : acc) {
        if (cnt == people) {
          ++sum;
        }
      }
      acc.clear();
      people = 0;
      continue;
    }
    ++people;
    for (const auto& c : row) {
      if (!acc.contains(c)) {
        acc[c] = 0;
      }
      ++acc[c];
    }
  }
  for (const auto& [c, cnt] : acc) {
    if (cnt == people) {
      ++sum;
    }
  }
  return sum;
}

}  // namespace

absl::StatusOr<int64_t> Yes(const std::vector<std::string>& entries,
                            bool second) {
  if (!second) {
    return CountUniqueAnswers(entries);
  }
  return CountUniqueAnswersAll(entries);
}

