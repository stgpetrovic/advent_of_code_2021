#include "day05/solution.h"

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

constexpr int32_t kMax = 1e3;

struct Point {
  int32_t x;
  int32_t y;

  Point(int32_t x_in, int32_t y_in) {
    x = x_in;
    y = y_in;
  }

  Point(absl::string_view in) {
    std::vector<std::string> parts = absl::StrSplit(in, ",");
    CHECK(absl::SimpleAtoi(parts[0], &x));
    CHECK(absl::SimpleAtoi(parts[1], &y));
  }

  template <typename H>
  friend H AbslHashValue(H h, const Point& p) {
    return H::combine(std::move(h), p.x, p.y);
  }

  Point() = default;
};

bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << '(' << p.x << ',' << p.y << ')';
  return os;
}

struct Line {
  Point begin;
  Point end;
  double k;

  Line(absl::string_view in) {
    std::vector<std::string> parts = absl::StrSplit(in, " -> ");
    begin = Point(parts[0]);
    end = Point(parts[1]);
    k = (1.0f * end.y - begin.y) / (1.0f * end.x - begin.x);
  }

  bool IsHorizontalOrVertical() const {
    return begin.x == end.x || begin.y == end.y;
  }

  bool Parallel(const Line& other) {
    return std::abs(other.k - k) < std::numeric_limits<double>::epsilon();
  }
};

std::ostream& operator<<(std::ostream& os, const Line& l) {
  os << l.begin << " -> " << l.end;
  return os;
}

class Field {
 public:
  Field(const std::vector<std::string>& in) {
    for (const auto& line : in) {
      lines.emplace_back(line);
    }
  }

  friend std::ostream& operator<<(std::ostream& o, Field const& f) {
    for (const auto& line : f.lines) {
      o << line << std::endl;
    }
    return o;
  }

  std::vector<Line> lines;
};

}  // namespace

absl::StatusOr<int32_t> DangerousFumes(const std::vector<std::string>& input,
                                       bool consider_diagonals) {
  Field f(input);
  LOG(INFO) << f;

  short b[kMax][kMax] = {};
  absl::flat_hash_set<Point> sol;

  for (const auto& line : f.lines) {
    if (consider_diagonals || line.IsHorizontalOrVertical()) {
      if (line.begin.x == line.end.x) {  // vertical
        for (int j = std::min(line.begin.y, line.end.y);
             j <= std::max(line.begin.y, line.end.y); ++j) {
          if (++b[line.begin.x][j] >= 2) {
            sol.insert(Point{line.begin.x, j});
          }
        }
      } else if (line.begin.y == line.end.y) {  // horizontal
        for (int i = std::min(line.begin.x, line.end.x);
             i <= std::max(line.begin.x, line.end.x); ++i) {
          if (++b[i][line.begin.y] >= 2) {
            sol.insert(Point{i, line.begin.y});
          }
        }
      } else {  // diagonal
        Point left, right;
        if (line.begin.x <= line.end.x) {
          left = line.begin;
          right = line.end;
        } else {
          left = line.end;
          right = line.begin;
        }

        for (int x = left.x, y = left.y; x <= right.x;
             ++x, y += left.y <= right.y ? 1 : -1) {
          if (++b[x][y] >= 2) {
            sol.insert(Point{x, y});
          }
        }
      }
    }
  }

  return sol.size();
}
