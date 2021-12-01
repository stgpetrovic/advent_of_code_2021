#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day12/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day12, First) {
  std::vector<std::string> input = {"F10", "N3", "F7", "R90", "F11"};

  auto result = Sail(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 25);
}

TEST(Day12, Second) {
  std::vector<std::string> input = {"F10", "N3", "F7", "R90", "F11"};

  auto result = Sail(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 286);
}
