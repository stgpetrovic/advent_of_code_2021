#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day09/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day09, First) {
  std::vector<std::string> input = {
      "35",  "20",  "15",  "25",  "47",  "40",  "62",  "55",  "65",  "95",
      "102", "117", "150", "182", "127", "219", "299", "277", "309", "576"};

  auto result = Count(input, 5);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 127);
}

TEST(Day09, Second) {
  std::vector<std::string> input = {
      "35",  "20",  "15",  "25",  "47",  "40",  "62",  "55",  "65",  "95",
      "102", "117", "150", "182", "127", "219", "299", "277", "309", "576"};

  auto result = Count(input, 5, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 62);
}
