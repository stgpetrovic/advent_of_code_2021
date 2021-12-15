#include <vector>

#include "day15/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day15, First) {
  std::vector<std::string> input = {
      "1163751742", "1381373672", "2136511328", "3694931569", "7463417111",
      "1319128137", "1359912421", "3125421639", "1293138521", "2311944581"};

  auto result = FindExit(input, /*large=*/false);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 40);
}

TEST(Day15, Second) {
  std::vector<std::string> input = {
      "1163751742", "1381373672", "2136511328", "3694931569", "7463417111",
      "1319128137", "1359912421", "3125421639", "1293138521", "2311944581"};

  auto result = FindExit(input, /*large=*/true);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 315);
}
