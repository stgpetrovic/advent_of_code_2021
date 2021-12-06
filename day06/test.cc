#include <vector>

#include "day06/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day06, First) {
  std::vector<std::string> input = {"3,4,3,1,2"};

  auto result = Spawn(input, 80);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 5934);
}

TEST(Day06, Second) {
  std::vector<std::string> input = {"3,4,3,1,2"};

  auto result = Spawn(input, 256);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 26984457539);
}
