#include <vector>

#include "day02/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day02, First) {
  std::vector<std::string> input = {"forward 5", "down 5", "forward 8",
                                    "up 3",      "down 8", "forward 2"};
  auto result = Navigate(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 150);
}

TEST(Day02, Second) {
  std::vector<std::string> input = {"forward 5", "down 5", "forward 8",
                                    "up 3",      "down 8", "forward 2"};
  auto result = NavigateWithAim(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 900);
}
