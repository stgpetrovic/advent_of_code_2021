#include "day15/solution.h"

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
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

namespace {

struct Point {
  int32_t x, y;

  Point operator+(const Point& other) const {
    return {.x = x + other.x, .y = y + other.y};
  }

  template <typename H>
  friend H AbslHashValue(H h, const Point& p) {
    return H::combine(std::move(h), p.x, p.y);
  }
};

bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

class Matrix {
 public:
  explicit Matrix(const std::vector<std::string>& lines)
      : dimx_(lines.size()), dimy_(lines[0].length()) {
    for (int i = 0; i < lines.size(); ++i) {
      for (int j = 0; j < lines[i].length(); ++j) {
        d_[i][j] = lines[i][j] - '0';
      }
    }
  }

  int32_t Translate(int32_t i, int32_t j) {
    int32_t d = i / dimx_ + j / dimy_;
    i = i % dimx_;
    j = j % dimy_;
    int32_t x = d_[i][j] + d;
    if (x % 9 != 0) {
      x %= 9;
    }
    return x;
  }

  int32_t DescendExit(bool large) {
    int32_t dimx = (large ? 5 : 1) * dimx_;
    int32_t dimy = (large ? 5 : 1) * dimy_;
    int D[550][550];
    for (int i = 0; i < dimx + 10; ++i) {
      for (int j = 0; j < dimy + 10; ++j) {
        D[i][j] = std::numeric_limits<int32_t>::max();
      }
    }

    // I can get to these corners in a cheaper way potentially,
    // but I'll just run the solver n times till it finds the
    // cheapest path.
    int32_t sum = 0;
    for (int i = 0; i < dimx; ++i) {
      sum += Translate(i, 0);
      D[i][0] = sum;
    }
    sum = 0;
    for (int j = 0; j < dimy; ++j) {
      sum += Translate(0, j);
      D[0][j] = sum;
    }

    bool changed = true;
    int32_t sol = 0;
    while (changed) {
      for (int i = 1; i < dimx; ++i) {
        for (int j = 1; j < dimy; ++j) {
          int32_t min = std::min({
              D[i - 1][j],
              D[i + 1][j],
              D[i][j + 1],
              D[i][j - 1],
          });
          D[i][j] = min + Translate(i, j);
        }
      }
      int32_t curr = D[dimx - 1][dimy - 1] - d_[0][0];
      changed = sol != curr;
      sol = curr;
    }
    return sol;
  }

 private:
  int32_t dimx_, dimy_;
  short d_[101][101] = {};
};

}  // namespace

absl::StatusOr<int64_t> FindExit(const std::vector<std::string>& input,
                                 bool large) {
  Matrix matrix(input);
  return matrix.DescendExit(large);
}
