#include <vector>

#include "day01/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day01, First) {
  std::vector<int32_t> input = {199, 200, 208, 210, 200,
                                207, 240, 269, 260, 263};
  auto result = CountIncreases(input);
  ASSERT_EQ(result, 7);
}

TEST(Day01, Second) {
  std::vector<int32_t> input = {199, 200, 208, 210, 200,
                                207, 240, 269, 260, 263};
  auto result = CountWindowIncreases(input);
  ASSERT_EQ(result, 5);
}
