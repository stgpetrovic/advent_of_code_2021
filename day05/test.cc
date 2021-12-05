#include <vector>

#include "day05/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day05, First) {
  std::vector<std::string> input = {
      "0,9 -> 5,9", "8,0 -> 0,8", "9,4 -> 3,4", "2,2 -> 2,1", "7,0 -> 7,4",
      "6,4 -> 2,0", "0,9 -> 2,9", "3,4 -> 1,4", "0,0 -> 8,8", "5,5 -> 8,2"};

  auto result = DangerousFumes(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 5);
}

TEST(Day05, Second) {
  std::vector<std::string> input = {
      "0,9 -> 5,9", "8,0 -> 0,8", "9,4 -> 3,4", "2,2 -> 2,1", "7,0 -> 7,4",
      "6,4 -> 2,0", "0,9 -> 2,9", "3,4 -> 1,4", "0,0 -> 8,8", "5,5 -> 8,2"};

  auto result = DangerousFumes(input, /*consider_diagonals=*/true);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 12);
}
