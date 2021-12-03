#include <vector>

#include "day03/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day02, First) {
  std::vector<std::string> input = {"00100", "11110", "10110", "10111",
                                    "10101", "01111", "00111", "11100",
                                    "10000", "11001", "00010", "01010"};
  auto result = Power(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 198);
}

TEST(Day02, Second) {
  std::vector<std::string> input = {"00100", "11110", "10110", "10111",
                                    "10101", "01111", "00111", "11100",
                                    "10000", "11001", "00010", "01010"};
  auto result = LifeSupport(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 230);
}
