#include "day13/solution.h"

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

  template <typename H>
  friend H AbslHashValue(H h, const Point& p) {
    return H::combine(std::move(h), p.x, p.y);
  }
};

bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

enum Direction { X = 0, Y = 1 };
struct Fold {
  Direction d;
  int32_t location;
};

class Foil {
 public:
  explicit Foil(const std::vector<std::string> lines) : dim_({.x = 0, .y = 0}) {
    for (const auto& line : lines) {
      if (line.empty()) {
        continue;
      }
      if (absl::StartsWith(line, "fold")) {
        std::vector<std::string> parts = absl::StrSplit(line, "=");
        int32_t location;
        CHECK(absl::SimpleAtoi(parts[1], &location));
        Direction d = line[11] == 'x' ? X : Y;
        folds_.push_back({.d = d, .location = location});
      } else {
        std::vector<std::string> parts = absl::StrSplit(line, ",");
        Point p;
        CHECK(absl::SimpleAtoi(parts[0], &p.x));
        CHECK(absl::SimpleAtoi(parts[1], &p.y));
        points_.insert(p);
        dim_.x = std::max(dim_.x, p.x);
        dim_.y = std::max(dim_.y, p.y);
      }
    }
  }

  int32_t VisiblePoints() const { return points_.size(); }

  void ApplyFolds(int32_t num_folds = -1) {
    for (const auto& f : folds_) {
      if (num_folds-- == 0) {
        return;
      }
      Apply(f);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Foil& f);

 private:
  void Apply(const Fold& f) {
    auto getter = [](const Point& p, Direction d) {
      return d == X ? p.x : p.y;
    };
    auto folder = [](const Point& p, const Fold& f) {
      return f.d == X ? Point{.x = 2 * f.location - p.x, .y = p.y}
                      : Point{.x = p.x, .y = 2 * f.location - p.y};
    };
    absl::flat_hash_set<Point> points_copy{points_};
    for (const auto& p : points_copy) {
      if (getter(p, f.d) > f.location) {
        points_.erase(p);
        points_.insert(folder(p, f));
      }
    }
  }

  absl::flat_hash_set<Point> points_;
  std::vector<Fold> folds_;
  Point dim_;
};

std::ostream& operator<<(std::ostream& os, const Foil& f) {
  for (int i = 0; i < f.dim_.x; ++i) {
    for (int j = 0; j < f.dim_.y; ++j) {
      os << (f.points_.contains({.x = i, .y = j}) ? "#" : " ");
    }
    os << std::endl;
  }
  return os;
}

}  // namespace

absl::StatusOr<int32_t> Fold(const std::vector<std::string>& input) {
  Foil f(input);
  f.ApplyFolds(/*num_folds=*/1);
  return f.VisiblePoints();
}

absl::StatusOr<int32_t> CameraCode(const std::vector<std::string>& input) {
  Foil f(input);
  f.ApplyFolds();
  std::cout << f << std::endl;
  LOG(INFO) << "Pipe this to vim and view with `:set nowrap`";
  return -1;
}
