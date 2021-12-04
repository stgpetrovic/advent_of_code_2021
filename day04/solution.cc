#include "day04/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

namespace {

constexpr int32_t kMax = 5;

class BingoBoard {
 public:
  BingoBoard(const std::vector<std::string> in) {
    for (int i = 0; i < 5; ++i) {
      std::string escaped = absl::StrReplaceAll(in[i], {{"  ", " "}});
      if (escaped[0] == ' ') {
        escaped.erase(0, 1);
      }
      std::vector<std::string> parts = absl::StrSplit(escaped, " ");
      for (int j = 0; j < 5; ++j) {
        int32_t n;
        escaped = absl::StrReplaceAll(parts[j], {{"  ", " "}});
        if (!absl::SimpleAtoi(escaped, &n)) {
          LOG(FATAL) << "Failed to parse board to integers: " << escaped;
        }
        b_[i][j] = n;
        hits_[i][j] = false;
      }
    }
  }

  bool Hit(int32_t number) {
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (b_[i][j] == number) {
          hits_[i][j] = true;
          LOG(INFO) << " Hit " << number << "(" << i << " " << j << ")";
          latest_ = std::make_pair(i, j);
          return true;
        }
      }
    }
    return false;
  }

  int32_t DarkSum() {
    int32_t dark_sum = 0;
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (!hits_[i][j]) {
          dark_sum += b_[i][j];
        }
      }
    }
    LOG(INFO) << "Dark Sum " << dark_sum;
    return dark_sum;
  }

  bool Victory() {
    int32_t cnt = 0;
    for (int i = 0; i < 5; ++i) {
      if (hits_[i][latest_.second]) {
        ++cnt;
      }
    }
    if (cnt == kMax) {
      return true;
    }
    cnt = 0;
    for (int j = 0; j < 5; ++j) {
      if (hits_[latest_.first][j]) {
        ++cnt;
      }
    }
    return cnt == kMax;
  }

 private:
  int32_t b_[kMax][kMax];
  bool hits_[kMax][kMax];
  std::pair<size_t, size_t> latest_;
};

class Game {
 public:
  Game(const std::vector<std::string> input) {
    // Parse input.
    std::vector<std::string> parts = absl::StrSplit(input[0], ",");
    for (const auto& sn : parts) {
      int32_t n;
      if (!absl::SimpleAtoi(sn, &n)) {
        LOG(FATAL) << "Failed to parse input to integers.";
      }
      numbers_.push_back(n);
    }
    std::vector<std::string> board;
    for (int i = 2; i < input.size(); ++i) {
      LOG(INFO) << "Input " << i << " " << input[i] << ": "
                << input[i].length();
      if (input[i].empty() || input[i] == " ") {
        BingoBoard b(board);
        boards_.push_back(b);
        board.clear();
      } else {
        board.push_back(input[i]);
      }
    }
    BingoBoard b(board);
    boards_.push_back(b);
    LOG(INFO) << "Total boards: " << boards_.size();
  }

  int32_t Win() {
    for (const auto& number : numbers_) {
      LOG(INFO) << "Number drawn: " << number;
      for (int i = 0; i < boards_.size(); ++i) {
        if (boards_[i].Hit(number)) {
          LOG(INFO) << "Board " << i << " HIT!";
        }
        if (boards_[i].Victory()) {
          return boards_[i].DarkSum() * number;
        }
      }
    }
    return -1;
  }

  int32_t Lose() {
    absl::flat_hash_set<int32_t> win_indices;
    for (const auto& number : numbers_) {
      LOG(INFO) << "Number drawn: " << number;
      for (int i = 0; i < boards_.size(); ++i) {
        if (boards_[i].Hit(number)) {
          LOG(INFO) << "Board " << i << " HIT!";
        }
        if (boards_[i].Victory()) {
          win_indices.insert(i);
          if (win_indices.size() == boards_.size()) {
            return boards_[i].DarkSum() * number;
          }
        }
      }
    }
    return -1;
  }

 private:
  std::vector<BingoBoard> boards_;
  std::vector<int32_t> numbers_;
};

}  // namespace

absl::StatusOr<int32_t> Bingo(const std::vector<std::string>& input) {
  return Game(input).Win();
}

absl::StatusOr<int32_t> BingoLose(const std::vector<std::string>& input) {
  return Game(input).Lose();
}
