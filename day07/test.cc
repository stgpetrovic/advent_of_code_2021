#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "day07/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day07, First) {
  std::vector<std::string> input = {
      "light red bags contain 1 bright white bag, 2 muted yellow bags.",
      "dark orange bags contain 3 bright white bags, 4 muted yellow bags.",
      "bright white bags contain 1 shiny gold bag.",
      "muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.",
      "shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.",
      "dark olive bags contain 3 faded blue bags, 4 dotted black bags.",
      "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.",
      "faded blue bags contain no other bags.",
      "dotted black bags contain no other bags."};

  auto result = Bags(input);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 4);
}

TEST(Day07, Second) {
  std::vector<std::string> input = {
      "light red bags contain 1 bright white bag, 2 muted yellow bags.",
      "dark orange bags contain 3 bright white bags, 4 muted yellow bags.",
      "bright white bags contain 1 shiny gold bag.",
      "muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.",
      "shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.",
      "dark olive bags contain 3 faded blue bags, 4 dotted black bags.",
      "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.",
      "faded blue bags contain no other bags.",
      "dotted black bags contain no other bags."};

  auto result = Bags(input, true);
  ASSERT_TRUE(result.ok());
  ASSERT_EQ(*result, 32);
}
