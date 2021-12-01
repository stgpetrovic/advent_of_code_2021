#include <vector>

#include "absl/status/statusor.h"
#include "day02/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day01, First) {
  std::vector<std::string> input = {"1-3 a: abcde", "1-3 b: cdefg",
                                    "2-9 c: ccccccccc"};

  auto result = ValidPasswords(input, 1);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 2);
}

TEST(Day01, Second) {
  std::vector<std::string> input = {"1-3 a: abcde", "1-3 b: cdefg",
                                    "2-9 c: ccccccccc"};

  auto result = ValidPasswords(input, 2);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 1);
}
