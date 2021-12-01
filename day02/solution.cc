#include "day02/solution.h"

#include <vector>

#include "absl/algorithm/container.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

namespace {
struct PassValidation {
  int32_t min;
  int32_t max;
  char letter;
  std::string password;

  bool IsValid(int policy) const {
    if (policy == 1) {
      auto letter_count = absl::c_count(password, letter);
      return letter_count >= min && letter_count <= max;
    } else if (policy == 2) {
      return ((password[min - 1] == letter && password[max - 1] != letter) ||
              (password[min - 1] != letter && password[max - 1] == letter));
    }
    CHECK(false);
  }
};

std::vector<PassValidation> ParseCases(
    const std::vector<std::string>& entries) {
  std::vector<PassValidation> pass_validations;
  for (const auto& entry : entries) {
    PassValidation pass_validation;
    std::vector<std::string> parts = absl::StrSplit(entry, ":");
    pass_validation.password = parts[1].substr(1);
    std::vector<std::string> validation_parts = absl::StrSplit(parts[0], ' ');
    pass_validation.letter = validation_parts[1][0];
    std::vector<std::string> range_parts =
        absl::StrSplit(validation_parts[0], '-');
    CHECK(absl::SimpleAtoi(range_parts[0], &pass_validation.min));
    CHECK(absl::SimpleAtoi(range_parts[1], &pass_validation.max));
    pass_validations.push_back(pass_validation);
  }
  return pass_validations;
}

}  // namespace

absl::StatusOr<int32_t> ValidPasswords(const std::vector<std::string>& entries,
                                       int policy) {
  auto validation_cases = ParseCases(entries);

  return absl::c_count_if(validation_cases,
                          [&policy](const PassValidation& pass_validation) {
                            return pass_validation.IsValid(policy);
                          });
}

