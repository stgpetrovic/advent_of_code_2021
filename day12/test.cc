#include <vector>

#include "day12/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day12, Simple) {
  std::vector<std::string> input = {"start-A", "start-b", "A-c",  "A-b",
                                    "b-d",     "A-end",   "b-end"};
  auto result = Caves(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 10);

  result = CavesRepetition(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 36);
}

TEST(Day12, Intermediate) {
  std::vector<std::string> input = {
      "dc-end", "HN-start", "start-kj", "dc-start", "dc-HN",
      "LN-dc",  "HN-end",   "kj-sa",    "kj-HN",    "kj-dc"};
  auto result = Caves(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 19);

  result = CavesRepetition(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 103);
}

TEST(Day12, Hard) {
  std::vector<std::string> input = {
      "fs-end", "he-DX",    "fs-he", "start-DX", "pj-DX", "end-zg",
      "zg-sl",  "zg-pj",    "pj-he", "RW-he",    "fs-DX", "pj-RW",
      "zg-RW",  "start-pj", "he-WI", "zg-he",    "pj-fs", "start-RW"};
  auto result = Caves(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 226);

  result = CavesRepetition(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 3509);
}
