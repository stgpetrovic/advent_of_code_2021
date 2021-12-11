#include "day11/solution.h"

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
};

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

  int64_t Step() {
    std::vector<std::vector<bool>> flashed(dimx_, std::vector<bool>(dimy_));

    // First, the energy level of each octopus increases by 1.
    for (int i = 0; i < dimx_; ++i) {
      for (int j = 0; j < dimy_; ++j) {
        ++d_[i][j];
      }
    }

    // This process continues as long as new octopuses keep having their energy
    // level increased beyond 9.
    bool any_flashed = true;
    while (any_flashed) {
      any_flashed = false;
      for (int i = 0; i < dimx_; ++i) {
        for (int j = 0; j < dimy_; ++j) {
          const auto& p = Point{.x = i, .y = j};
          // Then, any octopus with an energy level greater than 9 flashes.
          if (!flashed[p.x][p.y] && Value(p) > 9) {
            flashed[p.x][p.y] = true;
            any_flashed = true;

            // This increases the energy level of all adjacent octopuses by 1.
            for (const auto& adj : Adjecent(p)) {
              ++d_[adj.x][adj.y];
            }
          }
        }
      }
    }

    // Finally, any octopus that flashed during this step has its energy level
    // set to 0, as it used all of its energy to flash.
    int64_t total_flashes = 0;
    for (int i = 0; i < dimx_; ++i) {
      for (int j = 0; j < dimy_; ++j) {
        if (flashed[i][j]) {
          ++total_flashes;
          d_[i][j] = 0;
        }
      }
    }

    return total_flashes;
  }

 private:
  short Value(const Point& p) { return d_[p.x][p.y]; }

  bool Fits(const Point& p) {
    return p.x >= 0 && p.y >= 0 && p.x < dimx_ && p.y < dimy_;
  }

  std::vector<Point> Adjecent(const Point& p) {
    std::vector<Point> points;
    for (const Point& n : std::vector<Point>{
             {.x = 1, .y = 0},
             {.x = -1, .y = 0},
             {.x = 0, .y = 1},
             {.x = 0, .y = -1},
             {.x = -1, .y = -1},
             {.x = 1, .y = 1},
             {.x = -1, .y = 1},
             {.x = 1, .y = -1},
         }) {
      const auto candidate = p + n;
      if (Fits(candidate)) {
        points.push_back(candidate);
      }
    }
    return points;
  }

  size_t dimx_, dimy_;
  short d_[10][10] = {};
};

}  // namespace

absl::StatusOr<int64_t> DumboFlashes(const std::vector<std::string>& input) {
  Matrix matrix(input);
  int64_t total_flashes = 0;
  for (int i = 0; i < 100; ++i) {
    total_flashes += matrix.Step();
  }
  return total_flashes;
}

absl::StatusOr<int64_t> DumboSync(const std::vector<std::string>& input) {
  Matrix matrix(input);
  int64_t steps = 0;
  while (++steps) {
    if (matrix.Step() == 100) {
      break;
    }
    if (steps % 1000 == 0) {
      LOG(INFO) << "step " << steps;
    }
  }
  return steps;
}
