#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day05/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day05, First) {
  absl::flat_hash_map<std::string, int> input = {{"FBFBBFFRLR", 357},
                                                 {"BFFFBBFRRR", 567},
                                                 {"FFFBBBFRRR", 119},
                                                 {"BBFFBBFRLL", 820}};

  for (const auto& [code, want] : input) {
    auto result = SeatId({code});
    ASSERT_TRUE(result.ok());
    ASSERT_EQ(*result, want);
  }
}
