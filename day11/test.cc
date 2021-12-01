#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day11/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day11, First) {
  std::vector<std::string> input = {
      "L.LL.LL.LL", "LLLLLLL.LL", "L.L.L..L..", "LLLL.LL.LL", "L.LL.LL.LL",
      "L.LLLLL.LL", "..L.L.....", "LLLLLLLLLL", "L.LLLLLL.L", "L.LLLLL.LL"};

  auto result = Seats(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 37);
}

TEST(Day11, Second) {
  std::vector<std::string> input = {
      "L.LL.LL.LL", "LLLLLLL.LL", "L.L.L..L..", "LLLL.LL.LL", "L.LL.LL.LL",
      "L.LLLLL.LL", "..L.L.....", "LLLLLLLLLL", "L.LLLLLL.L", "L.LLLLL.LL"};

  auto result = Seats(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 26);
}
