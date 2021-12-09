#include "day09/solution.h"

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

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
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

  std::vector<Point> LowPoints() {
    std::vector<Point> low_points;
    for (int i = 0; i < dimx_; ++i) {
      for (int j = 0; j < dimy_; ++j) {
        const Point current = {.x = i, .y = j};
        if (absl::c_all_of(Adjecent(current),
                           [this, &current](const Point& adj) {
                             return Value(adj) > Value(current);
                           })) {
          low_points.push_back(current);
        }
      }
    }
    return low_points;
  }

  short Value(const Point& p) { return d_[p.x][p.y]; }

  int32_t Basin(const Point& p) {
    bool** visited = new bool*[dimx_];
    for (int i = 0; i < dimx_; ++i) {
      visited[i] = new bool[dimy_];
      for (int j = 0; j < dimy_; ++j) {
        visited[i][j] = false;
      }
    }

    std::vector<Point> q;
    q.push_back(p);
    visited[p.x][p.y] = true;

    Point v;
    int32_t basin_size = 0;
    while (!q.empty()) {
      v = q[0];

      LOG(INFO) << "Visiting " << p;
      ++basin_size;
      q.erase(q.begin());

      for (const auto& p : Adjecent(v)) {
        LOG(INFO) << "Adj " << p << " visited " << visited[p.x][p.y]
                  << " value " << Value(p);
        if (!visited[p.x][p.y]) {
          if (Value(p) != 9 && Value(p) > Value(v)) {
            q.push_back(p);
            visited[p.x][p.y] = true;
          }
        }
      }
    }

    for (int i = 0; i < dimx_; ++i) {
      delete[] visited[i];
    }
    delete[] visited;
    LOG(INFO) << "Basin size of " << p << " is " << basin_size;
    return basin_size;
  }

 private:
  bool Fits(const Point& p) {
    return p.x >= 0 && p.y >= 0 && p.x < dimx_ && p.y < dimy_;
  }

  std::vector<Point> Adjecent(const Point& p) {
    std::vector<Point> points;
    for (const Point& n : std::vector<Point>{{.x = 1, .y = 0},
                                             {.x = -1, .y = 0},
                                             {.x = 0, .y = 1},
                                             {.x = 0, .y = -1}}) {
      const auto candidate = p + n;
      if (Fits(candidate)) {
        points.push_back(candidate);
      }
    }
    return points;
  }

  size_t dimx_, dimy_;
  short d_[100][100] = {};
};

}  // namespace

absl::StatusOr<int32_t> RiskLevels(const std::vector<std::string>& input) {
  Matrix matrix(input);
  return absl::c_accumulate(matrix.LowPoints(), 0,
                            [&matrix](int32_t acc, const Point& p) {
                              return acc + 1 + matrix.Value(p);
                            });
}

absl::StatusOr<int32_t> Basins(const std::vector<std::string>& input) {
  Matrix matrix(input);

  std::vector<int32_t> basin_sizes;
  absl::c_transform(matrix.LowPoints(), std::back_inserter(basin_sizes),
                    [&matrix](const Point& p) { return matrix.Basin(p); });
  absl::c_sort(basin_sizes, std::greater<int32_t>());
  return std::accumulate(basin_sizes.begin(), basin_sizes.begin() + 3, 1,
                         [](int32_t acc, int32_t size) { return acc * size; });
}
