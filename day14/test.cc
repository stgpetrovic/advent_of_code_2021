#include <vector>

#include "day14/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day14, First) {
  std::vector<std::string> input = {
      "NNCB",    "        ", "CH -> B", "HH -> N", "CB -> H", "NH -> C",
      "HB -> C", "HC -> B",  "HN -> C", "NN -> C", "BH -> H", "NC -> B",
      "NB -> B", "BN -> B",  "BB -> N", "BC -> B", "CC -> N", "CN -> C"};

  auto result = Polymer(input, /*steps=*/10);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 1588);
}

TEST(Day14, Second) {
  std::vector<std::string> input = {
      "NNCB",    "        ", "CH -> B", "HH -> N", "CB -> H", "NH -> C",
      "HB -> C", "HC -> B",  "HN -> C", "NN -> C", "BH -> H", "NC -> B",
      "NB -> B", "BN -> B",  "BB -> N", "BC -> B", "CC -> N", "CN -> C"};

  auto result = Polymer(input, /*steps=*/40);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 2188189693529);
}
