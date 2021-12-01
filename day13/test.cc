#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_join.h"
#include "day13/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day13, First) {
  std::vector<std::string> input = {"939", "7,13,x,x,59,x,31,19"};

  auto result = Bus(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 295);
}

TEST(Day13, Second) {
  absl::flat_hash_map<int64_t, std::vector<std::string>> inputs = {
      {1068781, {"0", "7,13,x,x,59,x,31,19"}},
      {3417, {"0", "17,x,13,19"}},
      {754018, {"0", "67,7,59,61"}},
      {779210, {"0", "67,x,7,59,61"}},
      {1261476, {"0", "67,7,x,59,61"}},
      {1202161486, {"0", "1789,37,47,1889"}}};

  for (const auto& [want, input] : inputs) {
    std::cout << absl::StrJoin(input, " ") << "\n" << std::endl;
    auto result = Bus(input, true);
    ASSERT_TRUE(result.ok());
    ASSERT_EQ(*result, want);
    std::cout << "\nOK\n" << std::endl;
  }
}
