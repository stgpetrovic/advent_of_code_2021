#include "day08/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

namespace {

std::set<int32_t> PotentialDigits(absl::string_view segments) {
  switch (segments.length()) {
    case 2:
      return {1};
    case 3:
      return {7};
    case 4:
      return {4};
    case 5:
      return {2, 3, 5};
    case 6:
      return {6, 9, 0};
    case 7:
      return {8};
    default:
      return {};
  }
}

struct State {
  std::vector<std::string> readouts;
  std::vector<std::string> output;

  State(absl::string_view line) {
    std::vector<std::string> parts = absl::StrSplit(line, " | ");
    readouts = absl::StrSplit(parts[0], ' ');
    output = absl::StrSplit(parts[1], ' ');
  }
};

std::set<char> SegmentsForDigit(int32_t digit) {
  switch (digit) {
    case 0:
      return {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    case 1:
      return {'c', 'f'};
    case 2:
      return {'a', 'c', 'd', 'e', 'g'};
    case 3:
      return {'a', 'c', 'd', 'f', 'g'};
    case 4:
      return {'b', 'c', 'd', 'f'};
    case 5:
      return {'a', 'b', 'd', 'f', 'g'};
    case 6:
      return {'a', 'b', 'd', 'e', 'f', 'g'};
    case 7:
      return {'a', 'c', 'f'};
    case 8:
      return {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    case 9:
      return {'a', 'b', 'c', 'd', 'f', 'g'};
  }
  return {};
}

}  // namespace

absl::StatusOr<int32_t> Clock(const std::vector<std::string>& input) {
  std::vector<State> states;
  absl::c_transform(input, std::back_inserter(states),
                    [](const std::string& line) { return State(line); });
  return absl::c_accumulate(states, 0, [](int32_t sum, const State& r) {
    return sum + absl::c_accumulate(
                     r.output, 0, [](int32_t sum, const std::string& o) {
                       return sum += (PotentialDigits(o).size() == 1) ? 1 : 0;
                     });
  });
}

class Solver {
 public:
  explicit Solver(const State& state) : state_(state) { Solve(); }

  int32_t Value() {
    absl::flat_hash_map<std::set<char>, int32_t> rm;
    for (const auto& [k, v] : m_) {
      rm[v] = k;
    }
    std::string s;
    for (auto& o : state_.output) {
      s += absl::StrCat(rm[std::set<char>(o.begin(), o.end())]);
    }
    int32_t n;
    CHECK(absl::SimpleAtoi(s, &n));
    return n;
  }

 private:
  void Solve() {
    // easy: 1, 4, 7, 8.
    for (const auto& readout : state_.readouts) {
      const auto& potential_digits = PotentialDigits(readout);
      if (potential_digits.size() == 1) {
        m_[*potential_digits.begin()] =
            std::set<char>(readout.begin(), readout.end());
      }
    }

    // harder
    for (const auto& readout : state_.readouts) {
      auto s = std::set<char>(readout.begin(), readout.end());
      if (readout.length() == 6) {  // 0, 9, 6
        LOG(INFO) << readout;
        std::set<char> i;
        absl::c_set_intersection(s, m_[4], std::inserter(i, i.begin()));
        if (i.size() == 4) {  // 4=bcdf and 9=abcdfg share 4
          m_[9] = s;
        }
        i.clear();
        absl::c_set_intersection(s, m_[1], std::inserter(i, i.begin()));
        if (i.size() == 1) {  // 1=cf and 6=abdefg share 1
          m_[6] = s;
        }
      }
      if (readout.length() == 5) {  // 2, 3, 5
        LOG(INFO) << readout;
        std::set<char> i;
        absl::c_set_intersection(s, m_[7], std::inserter(i, i.begin()));
        if (i.size() == 3) {  // 3=acdfg and 7=acf share 3
          m_[3] = s;
        }
      }
    }

    // hardest
    for (const auto& readout : state_.readouts) {
      auto s = std::set<char>(readout.begin(), readout.end());
      if (readout.length() == 5) {  // 2, 3, 5
        LOG(INFO) << readout;
        std::set<char> i;
        absl::c_set_intersection(s, m_[6], std::inserter(i, i.begin()));
        if (i.size() == 5) {  // 6=abdefg and 5=abdfg share 5
          m_[5] = s;
        }
      }
    }

    // insane
    for (const auto& readout : state_.readouts) {
      LOG(INFO) << readout;
      auto s = std::set<char>(readout.begin(), readout.end());
      if (readout.length() == 5) {  // 2, 3, 5
        if (m_[5] != s && m_[3] != s) {
          m_[2] = s;
        }
      }
      if (readout.length() == 6) {  // 2, 3, 5
        if (m_[9] != s && m_[6] != s) {
          m_[0] = s;
        }
      }
    }
  }

  State state_;
  absl::flat_hash_map<int32_t, std::set<char>> m_;
};

absl::StatusOr<int32_t> ClockSum(const std::vector<std::string>& input) {
  std::vector<State> states;
  absl::c_transform(input, std::back_inserter(states),
                    [](const std::string& line) { return State(line); });

  return absl::c_accumulate(states, 0, [](int32_t acc, const State& state) {
    return acc + Solver(state).Value();
  });
}
