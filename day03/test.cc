#include <vector>

#include "absl/status/statusor.h"
#include "day03/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day03, First) {
  std::vector<std::string> input = {"..##.......", "#...#...#..", ".#....#..#.",
                                    "..#.#...#.#", ".#...##..#.", "..#.##.....",
                                    ".#.#.#....#", ".#........#", "#.##...#...",
                                    "#...##....#", ".#..#...#.#"};

  auto result = CountTrees(input, {{1, 3}});
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 7);
}

TEST(Day03, Second) {
  std::vector<std::string> input = {"..##.......", "#...#...#..", ".#....#..#.",
                                    "..#.#...#.#", ".#...##..#.", "..#.##.....",
                                    ".#.#.#....#", ".#........#", "#.##...#...",
                                    "#...##....#", ".#..#...#.#"};

  auto result = CountTrees(input, {{1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1}});
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 336);
}
