#include "day04/solution.h"

#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

namespace {
struct PassportData {
  int32_t birth_year;
  int32_t issue_year;
  int32_t expiration_year;
  std::string height;
  std::string hair_color;
  std::string eye_color;
  std::string passport_id;
  std::string country_id;

  bool BirthYearValid() const {
    return birth_year >= 1920 && birth_year <= 2002;
  }

  bool IssueYearValid() const {
    return issue_year >= 2010 && issue_year <= 2020;
  }

  bool ExpirationYearValid() const {
    return expiration_year >= 2020 && expiration_year <= 2030;
  }

  bool HeightValid() const {
    int number;
    if (absl::EndsWith(height, "in")) {
      return absl::SimpleAtoi(height.substr(0, height.length() - 2), &number) &&
             number >= 59 && number <= 76;
    } else if (absl::EndsWith(height, "cm")) {
      return absl::SimpleAtoi(height.substr(0, height.length() - 2), &number) &&
             number >= 150 && number <= 193;
    }
    return false;
  }

  bool HairColorValid() const {
    if (hair_color.length() != 7) {
      return false;
    }
    if (hair_color[0] != '#') {
      return false;
    }
    for (int i = 1; i < 7; ++i) {
      auto is_digit = hair_color[i] >= '0' && hair_color[i] <= '9';
      auto is_hex_letter = hair_color[i] >= 'a' && hair_color[i] <= 'f';
      if (!is_digit && !is_hex_letter) {
        return false;
      }
    }
    return true;
  }

  bool EyeColorValid() const {
    const static auto* const valid_eye_colors =
        new absl::flat_hash_set<std::string>{"amb", "blu", "brn", "gry",
                                             "grn", "hzl", "oth"};
    return valid_eye_colors->contains(eye_color);
  }

  bool PassportIdValid() const {
    int number;
    for (int i = 0; i < passport_id.length(); ++i) {
      if (passport_id[i] != '0') {
        return passport_id.length() == 9 &&
               absl::SimpleAtoi(passport_id.substr(i), &number);
      }
    }
    return false;
  }

  bool IsValid(bool strict) const {
    if (!strict) {
      return birth_year > 0 && issue_year > 0 && expiration_year > 0 &&
             !height.empty() && !hair_color.empty() && !eye_color.empty() &&
             !passport_id.empty();
    }
    return BirthYearValid() && IssueYearValid() && ExpirationYearValid() &&
           HeightValid() && HairColorValid() && EyeColorValid() &&
           PassportIdValid();
  }
};
}  // namespace

absl::StatusOr<int64_t> ValidPassports(const std::vector<std::string>& entries,
                                       bool strict) {
  std::vector<PassportData> passport_data;
  PassportData data;
  for (const auto& entry : entries) {
    if (entry.empty()) {
      passport_data.push_back(data);
      data = {};
    }
    std::vector<std::string> parts = absl::StrSplit(entry, ' ');
    for (const auto& part : parts) {
      std::vector<std::string> keyvalue = absl::StrSplit(part, ':');
      if (keyvalue[0] == "byr") {
        CHECK(absl::SimpleAtoi(keyvalue[1], &data.birth_year));
      } else if (keyvalue[0] == "iyr") {
        CHECK(absl::SimpleAtoi(keyvalue[1], &data.issue_year));
      } else if (keyvalue[0] == "eyr") {
        CHECK(absl::SimpleAtoi(keyvalue[1], &data.expiration_year));
      } else if (keyvalue[0] == "hgt") {
        data.height = keyvalue[1];
      } else if (keyvalue[0] == "hcl") {
        data.hair_color = keyvalue[1];
      } else if (keyvalue[0] == "ecl") {
        data.eye_color = keyvalue[1];
      } else if (keyvalue[0] == "pid") {
        data.passport_id = keyvalue[1];
      } else if (keyvalue[0] == "cid") {
        data.country_id = keyvalue[1];
      }
    }
  }
  passport_data.push_back(data);

  return absl::c_count_if(passport_data,
                          [&strict](const PassportData& passport) {
                            return passport.IsValid(strict);
                          });
}

