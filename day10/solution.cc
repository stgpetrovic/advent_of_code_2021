#include "day10/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <stack>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

namespace {

int64_t Reward(char offender, bool autocomplete) {
  static const auto* const scores = new absl::flat_hash_map<char, int64_t>{
      {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
  static const auto* const autocomplete_scores =
      new absl::flat_hash_map<char, int64_t>{
          {')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
  return autocomplete ? autocomplete_scores->at(offender)
                      : scores->at(offender);
}

char Friend(char c) {
  static const auto* const openers = new absl::flat_hash_map<char, char>{
      {')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}};
  static const auto* const closers = new absl::flat_hash_map<char, char>{
      {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
  auto it = openers->find(c);
  if (it != openers->end()) {
    return it->second;
  }
  return closers->at(c);
}

absl::StatusOr<int64_t> Parse(absl::string_view line, bool autocomplete) {
  std::stack<char> s;

  LOG(INFO) << "Analyzing " << line;
  for (const char& c : line) {
    switch (c) {
      case '(':
      case '[':
      case '{':
      case '<':
        s.push(c);
        continue;
      case ')':
      case ']':
      case '}':
      case '>':
        if (s.top() != Friend(c)) {
          if (autocomplete) {
            return absl::InvalidArgumentError("skipping corrupted sectors");
          }
          return Reward(c, autocomplete);
        }
        s.pop();
        continue;
      default:
        continue;
    }
  }
  if (s.empty()) {
    return absl::InternalError("all is ok; should not exist in input");
  }
  if (!autocomplete) {
    return absl::InternalError("incomplete expression");
  }
  int64_t score = 0;
  while (!s.empty()) {
    score = score * 5 + Reward(Friend(s.top()), autocomplete);
    s.pop();
  }
  return score;
}

}  // namespace

absl::StatusOr<int64_t> SyntaxScore(const std::vector<std::string>& input) {
  return absl::c_accumulate(input, 0, [](int64_t acc, const std::string& line) {
    auto offending_char = Parse(line, /*autocomplete=*/false);
    return acc + (offending_char.ok() ? *offending_char : 0);
  });
}

absl::StatusOr<int64_t> AutocompleteScore(
    const std::vector<std::string>& input) {
  std::vector<int64_t> scores;
  for (const auto& line : input) {
    auto res = Parse(line, /*autocomplete=*/true);
    if (res.ok()) {
      scores.push_back(*res);
    }
  }

  size_t n = scores.size() / 2;
  std::nth_element(scores.begin(), scores.begin() + n, scores.end());
  return scores[n];
}
