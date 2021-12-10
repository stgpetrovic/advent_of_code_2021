#include <vector>

#include "day10/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day10, First) {
  std::vector<std::string> input = {
      "[({(<(())[]>[[{[]{<()<>>", "[(()[<>])]({[<{<<[]>>(",
      "{([(<{}[<>[]}>{[]{[(<()>", "(((({<>}<{<{<>}{[]{[]{}",
      "[[<[([]))<([[{}[[()]]]",   "[{[{({}]{}}([{[{{{}}([]",
      "{<[[]]>}<{[{[{[]{()[[[]",  "[<(<(<(<{}))><([]([]()",
      "<{([([[(<>()){}]>(<<{{",   "<{([{{}}[<[[[<>{}]]]>[]]"};

  auto result = SyntaxScore(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 26397);
}

TEST(Day10, Second) {
  std::vector<std::string> input = {
      "[({(<(())[]>[[{[]{<()<>>", "[(()[<>])]({[<{<<[]>>(",
      "{([(<{}[<>[]}>{[]{[(<()>", "(((({<>}<{<{<>}{[]{[]{}",
      "[[<[([]))<([[{}[[()]]]",   "[{[{({}]{}}([{[{{{}}([]",
      "{<[[]]>}<{[{[{[]{()[[[]",  "[<(<(<(<{}))><([]([]()",
      "<{([([[(<>()){}]>(<<{{",   "<{([{{}}[<[[[<>{}]]]>[]]"};

  auto result = AutocompleteScore(input);
  ASSERT_TRUE(result.ok()) << result.status();
  ASSERT_EQ(*result, 288957);
}
