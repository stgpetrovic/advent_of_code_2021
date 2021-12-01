#include "day01/solution.h"

#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"

absl::StatusOr<int32_t> TwoSumsTo2020(const absl::flat_hash_set<int32_t>& numbers) {
  for (const auto& number : numbers) {
    if (numbers.contains(2020 - number)) {
      return number * (2020-number);
    }
  }
  return absl::UnknownError("bug");
}

absl::StatusOr<int32_t> ThreeSumsTo2020(const absl::flat_hash_set<int32_t>& numbers) {
  for (const auto& number1 : numbers) {
    for (const auto& number2 : numbers) {
      if (numbers.contains(2020 - number1 - number2)) {
        return (2020 - number1 - number2) * number1 * number2;
      }
    }
  }
  return absl::UnknownError("bug");
}

