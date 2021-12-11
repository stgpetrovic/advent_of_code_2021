#include <vector>

#include "day11/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day11, First) {
  std::vector<std::string> input = {
      "5483143223", "2745854711", "5264556173", "6141336146", "6357385478",
      "4167524645", "2176841721", "6882881134", "4846848554", "5283751526"};

  auto result = DumboFlashes(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 1656);
}

TEST(Day11, Second) {
  std::vector<std::string> input = {
      "5483143223", "2745854711", "5264556173", "6141336146", "6357385478",
      "4167524645", "2176841721", "6882881134", "4846848554", "5283751526"};

  auto result = DumboSync(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 195);
}
