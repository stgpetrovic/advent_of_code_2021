#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day10/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day10, First) {
  std::vector<std::string> input = {
      "28", "33", "18", "42", "31", "14", "46", "20", "48", "47", "24",
      "23", "49", "45", "19", "38", "39", "11", "1",  "32", "25", "35",
      "8",  "17", "7",  "9",  "4",  "2",  "34", "10", "3"};

  auto result = Jolt(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 220);
}

TEST(Day10, Second) {
  std::vector<std::string> input = {
      "28", "33", "18", "42", "31", "14", "46", "20", "48", "47", "24",
      "23", "49", "45", "19", "38", "39", "11", "1",  "32", "25", "35",
      "8",  "17", "7",  "9",  "4",  "2",  "34", "10", "3"};

  auto result = Jolt(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 19208);
}
