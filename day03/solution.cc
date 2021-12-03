#include "day03/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

namespace {

struct MajorityStatus {
  bool element;
  int32_t count;
  bool majority;
};

MajorityStatus Major(const std::vector<std::string>& votes, size_t offset) {
  int32_t count_ones = absl::c_count_if(
      votes, [offset](const std::string& vote) { return vote[offset] == '1'; });
  int32_t count_zeros = votes.size() - count_ones;
  return {.element = count_ones > votes.size() / 2,
          .count = std::max(count_ones, count_zeros),
          .majority = count_ones != count_zeros};
}

absl::StatusOr<int32_t> PerformFiltering(
    const std::vector<std::string>& input,
    std::function<void(absl::flat_hash_set<std::string>*, size_t)> filter) {
  absl::flat_hash_set<std::string> candidates(input.begin(), input.end());
  for (int offset = 0; offset < input[0].length(); ++offset) {
    filter(&candidates, offset);
    if (candidates.size() == 1) {
      return std::stoi(*candidates.begin(), nullptr, 2);
    }
  }
  return absl::InvalidArgumentError(
      absl::StrCat("could not reduce to 1: ", candidates.size()));
}

void FilterMatching(absl::flat_hash_set<std::string>* candidates, size_t offset,
                    char match) {
  auto it = candidates->begin();
  while (it != candidates->end()) {
    auto current = it++;
    if ((*current)[offset] != match) {
      candidates->erase(current);
    }
  }
}

void O2Filter(absl::flat_hash_set<std::string>* candidates, size_t offset) {
  auto major = Major(
      std::vector<std::string>(candidates->begin(), candidates->end()), offset);
  FilterMatching(candidates, offset,
                 major.majority ? (major.element ? '1' : '0') : '1');
}

void CO2Filter(absl::flat_hash_set<std::string>* candidates, size_t offset) {
  auto major = Major(
      std::vector<std::string>(candidates->begin(), candidates->end()), offset);
  FilterMatching(candidates, offset,
                 major.majority ? (major.element ? '0' : '1') : '0');
}

}  // namespace

absl::StatusOr<int32_t> Power(const std::vector<std::string>& input) {
  int32_t gamma = Major(input, 0).element;
  int32_t epsilon = !gamma;
  for (size_t i = 1; i < input[0].length(); ++i) {
    gamma <<= 1;
    epsilon <<= 1;
    if (Major(input, i).element) {
      gamma += 1;
    } else {
      epsilon += 1;
    }
  }
  return gamma * epsilon;
}

absl::StatusOr<int32_t> LifeSupport(const std::vector<std::string>& input) {
  auto o2 = PerformFiltering(input, O2Filter);
  if (!o2.ok()) {
    return o2.status();
  }
  auto co2 = PerformFiltering(input, CO2Filter);
  if (!co2.ok()) {
    return co2.status();
  }
  return *o2 * *co2;
}
