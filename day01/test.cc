#include "day01/solution.h"

#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day01, First) {
  absl::flat_hash_set<int32_t> input = {1721, 979, 366, 299, 675, 1456};

  auto result = TwoSumsTo2020(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 514579);
}

TEST(Day01, SecondFirst) {
  absl::flat_hash_set<int32_t> input = {1721, 979, 366, 299, 675, 1456};

  auto result = ThreeSumsTo2020(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 241861950);
}

TEST(Day01, NoSoluton) {
  ASSERT_FALSE(TwoSumsTo2020({1,2,3,}).ok());
  ASSERT_FALSE(ThreeSumsTo2020({1,2,3,}).ok());
}
