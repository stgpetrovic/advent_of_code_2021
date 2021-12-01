#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day17/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day17, First) {
  std::vector<std::string> input{".#.", "..#", "###"};
  auto result = Cubes(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 112);
}

TEST(Day17, Second) {
  std::vector<std::string> input{".#.", "..#", "###"};
  auto result = Cubes(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 848);
}
