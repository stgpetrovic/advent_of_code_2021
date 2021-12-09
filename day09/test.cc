#include <vector>

#include "day09/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day09, First) {
  std::vector<std::string> input = {"2199943210", "3987894921", "9856789892",
                                    "8767896789", "9899965678"};

  auto result = RiskLevels(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 15);
}

TEST(Day09, Second) {
  std::vector<std::string> input = {"2199943210", "3987894921", "9856789892",
                                    "8767896789", "9899965678"};

  auto result = Basins(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 1134);
}
