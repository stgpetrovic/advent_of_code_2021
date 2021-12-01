#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day15/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day15, First) {
  for (const auto [want, input] :
       absl::flat_hash_map<int, std::vector<int>>{{436, {0, 3, 6}},
                                                  {1, {1, 3, 2}},
                                                  {10, {2, 1, 3}},
                                                  {27, {1, 2, 3}},
                                                  {78, {2, 3, 1}},
                                                  {438, {3, 2, 1}},
                                                  {1836, {3, 1, 2}}}) {
    auto result = Numbers(input);
    ASSERT_TRUE(result.ok());
    ASSERT_EQ(*result, want);
  }
}

TEST(Day15, Second) {
  for (const auto [want, input] :
       absl::flat_hash_map<int, std::vector<int>>{{175594, {0, 3, 6}},
                                                  {2578, {1, 3, 2}},
                                                  {3544142, {2, 1, 3}},
                                                  {261214, {1, 2, 3}},
                                                  {6895259, {2, 3, 1}},
                                                  {18, {3, 2, 1}},
                                                  {362, {3, 1, 2}}}) {
    auto result = Numbers(input, true);
    ASSERT_TRUE(result.ok());
    ASSERT_EQ(*result, want);
  }
}
