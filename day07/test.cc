#include <vector>

#include "day07/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day07, First) {
  std::vector<std::string> input = {"16,1,2,0,4,2,7,1,2,14"};

  auto result = Crevetten(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 37);
}

TEST(Day08, First) {
  std::vector<std::string> input = {"16,1,2,0,4,2,7,1,2,14"};

  auto result = Crevetten(input, /*acc=*/true);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 168);
}
