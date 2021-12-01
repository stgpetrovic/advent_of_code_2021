#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day06/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day06, First) {
  std::vector<std::string> input = {"abc", "",  "a", "b", "c", "", "ab", "ac",
                                    "",    "a", "a", "a", "a", "", "b"};
  auto result = Yes(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 11);
}

TEST(Day06, Second) {
  std::vector<std::string> input = {"abc", "",  "a", "b", "c", "", "ab", "ac",
                                    "",    "a", "a", "a", "a", "", "b"};
  auto result = Yes(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 6);
}
