#include "day14/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <limits>
#include <list>
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

using TokenPair = std::pair<char, char>;

class Plastic {
 public:
  explicit Plastic(const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
      if (absl::StripLeadingAsciiWhitespace(line).empty()) {
        continue;
      }
      std::vector<std::string> parts = absl::StrSplit(line, " -> ");
      if (parts.size() == 1) {
        template_ = line;
      } else {
        // From AB, with AB->C, new tokens are AC and CB.
        grammar_[std::make_pair(parts[0][0], parts[0][1])].push_back(
            std::make_pair(parts[0][0], parts[1][0]));
        grammar_[std::make_pair(parts[0][0], parts[0][1])].push_back(
            std::make_pair(parts[1][0], parts[0][1]));
      }
    }
  }

  int64_t Expand(int64_t steps) {
    absl::flat_hash_map<TokenPair, int64_t> token_counts;
    for (auto it = template_.begin(); it != template_.end(); ++it) {
      auto itn = std::next(it);
      if (itn == template_.end()) {
        break;
      }
      ++token_counts[std::make_pair(*it, *itn)];
    }

    while (steps-- > 0) {
      ExpandStep(token_counts);
    }

    return Hash(token_counts);
  }

  int64_t Hash(const absl::flat_hash_map<TokenPair, int64_t>& token_counts) {
    absl::flat_hash_map<char, int64_t> counts{{template_[0], 1}};
    for (const auto& [pair, cnt] : token_counts) {
      counts[pair.second] += cnt;
    }

    int64_t min = std::numeric_limits<int64_t>::max();
    int64_t max = std::numeric_limits<int64_t>::min();
    for (const auto& [c, cnt] : counts) {
      LOG(INFO) << "finals " << c << " " << cnt;
      min = std::min(min, cnt);
      max = std::max(max, cnt);
    }
    return max - min;
  }

 private:
  void ExpandStep(absl::flat_hash_map<TokenPair, int64_t>& token_counts) {
    LOG(INFO) << "=======New step:";
    absl::flat_hash_map<TokenPair, int64_t> next_counts;
    for (const auto& [source_token, new_tokens] : grammar_) {
      for (const auto& new_token : new_tokens) {
        next_counts[new_token] += token_counts[source_token];
        LOG(INFO) << new_token.first << new_token.second << " grows by size of "
                  << source_token.first << source_token.second << ": "
                  << token_counts[source_token];
      }
    }
    token_counts = next_counts;
  }

  std::string template_;
  absl::flat_hash_map<TokenPair, std::vector<TokenPair>> grammar_;
};

}  // namespace

absl::StatusOr<int64_t> Polymer(const std::vector<std::string>& input,
                                int64_t steps) {
  Plastic p(input);
  return p.Expand(steps);
}
