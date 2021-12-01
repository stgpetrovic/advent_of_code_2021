#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day14/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day14, First) {
  std::vector<std::string> input = {
      "mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X", "mem[8] = 11",
      "mem[7] = 101", "mem[8] = 0"};

  auto result = Mask(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 165);
}

TEST(Day14, Second) {
  std::vector<std::string> input = {
      "mask = 000000000000000000000000000000X1001X", "mem[42] = 100",
      "mask = 00000000000000000000000000000000X0XX", "mem[26] = 1"};

  auto result = Mask(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 208);
}
