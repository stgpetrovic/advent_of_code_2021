#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day08/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day08, First) {
  std::vector<std::string> input = {"nop +0", "acc +1", "jmp +4",
                                    "acc +3", "jmp -3", "acc -99",
                                    "acc +1", "jmp -4", "acc +6"};

  auto result = Parse(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 5);
}

TEST(Day08, Second) {
  std::vector<std::string> input = {"nop +0", "acc +1", "jmp +4",
                                    "acc +3", "jmp -3", "acc -99",
                                    "acc +1", "jmp -4", "acc +6"};

  auto result = Parse(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 8);
}
