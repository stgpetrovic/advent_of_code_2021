#include "day17/solution.h"

#include <bitset>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

namespace {
//
}  // namespace

struct Point {
  int x, y, z;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  bool operator!=(const Point& other) const { return !(*this == other); }

  bool operator<(const Point& other) const {
    return std::tie(x, y, x) < std::tie(other.x, other.y, other.z);
  }

  template <typename H>
  friend H AbslHashValue(H h, const Point& p) {
    return H::combine(std::move(h), p.x, p.y, p.z);
  }
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << '(' << p.x << ", " << p.y << ", " << p.z << ')';
  return os;
}

class Vasiona {
 public:
  Vasiona(int rounds, const std::vector<std::string>& input)
      : rounds_(rounds), board_(input.size()) {
    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        for (int k = 0; k < 20; ++k) {
          state_[i][j][k] = false;
        }
      }
    }

    for (int i = rounds_; i < rounds_ + input.size(); ++i) {
      for (int j = rounds_; j < rounds_ + input[i - rounds_].size(); ++j) {
        state_[i][j][rounds_] = input[i - rounds_][j - rounds_] == '#';
      }
    }
  }

  bool IsActive(const Point& p) const { return state_[p.x][p.y][p.z]; }
  void Activate(const Point& p) { state_[p.x][p.y][p.z] = true; }
  void Deactivate(const Point& p) { state_[p.x][p.y][p.z] = false; }

  bool Valid(const Point& p) {
    return p.x >= 0 && p.x < 20 && p.y >= 0 && p.y < 20 && p.z >= 0 && p.z < 20;
  }

  int ActiveNeighbors(const Point& p) {
    int active_neighbors = 0;

    for (const int dx : {0, -1, 1}) {
      for (const int dy : {0, -1, 1}) {
        for (const int dz : {0, -1, 1}) {
          if (dx == 0 && dy == 0 && dz == 0) {
            continue;
          }
          Point neighbor = {p.x + dx, p.y + dy, p.z + dz};
          if (Valid(neighbor) && IsActive(neighbor)) {
            ++active_neighbors;
          }
        }
      }
    }

    return active_neighbors;
  }

  int CountActive() const {
    int active = 0;
    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        for (int k = 0; k < 20; ++k) {
          if (IsActive(Point{i, j, k})) {
            ++active;
          }
        }
      }
    }
    return active;
  }

  void Simulate() {
    std::vector<Point> to_activate, to_deactivate;

    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        for (int k = 0; k < 20; ++k) {
          int active_neighbors = ActiveNeighbors({i, j, k});
          if (IsActive({i, j, k}) &&
              !(active_neighbors == 2 || active_neighbors == 3)) {
            to_deactivate.push_back({i, j, k});
          }
          if (!IsActive({i, j, k}) && active_neighbors == 3) {
            to_activate.push_back({i, j, k});
          }
        }
      }
    }

    std::cout << "Activating " << to_activate.size() << std::endl;
    for (const auto& p : to_activate) {
      Activate(p);
    }
    std::cout << "Deactivating " << to_deactivate.size() << std::endl;
    for (const auto& p : to_deactivate) {
      Deactivate(p);
    }
  }

 private:
  int rounds_;
  int board_;
  bool state_[20][20][20];
};

// Lazy, swimming > code health.

struct Point4 {
  int x, y, z, w;

  bool operator==(const Point4& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  bool operator!=(const Point4& other) const { return !(*this == other); }

  bool operator<(const Point4& other) const {
    return std::tie(x, y, x, w) < std::tie(other.x, other.y, other.z, other.w);
  }

  template <typename H>
  friend H AbslHashValue(H h, const Point4& p) {
    return H::combine(std::move(h), p.x, p.y, p.z, p.w);
  }
};

std::ostream& operator<<(std::ostream& os, const Point4& p) {
  os << '(' << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ')';
  return os;
}

class Vasiona4 {
 public:
  Vasiona4(int rounds, const std::vector<std::string>& input)
      : rounds_(rounds), board_(input.size()) {
    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        for (int k = 0; k < 20; ++k) {
          for (int l = 0; l < 20; ++l) {
            state_[i][j][k][l] = false;
          }
        }
      }
    }

    for (int i = rounds_; i < rounds_ + input.size(); ++i) {
      for (int j = rounds_; j < rounds_ + input.size(); ++j) {
        state_[i][j][rounds_][rounds_] = input[i - rounds_][j - rounds_] == '#';
      }
    }
  }

  bool IsActive(const Point4& p) const { return state_[p.x][p.y][p.z][p.w]; }
  void Activate(const Point4& p) { state_[p.x][p.y][p.z][p.w] = true; }
  void Deactivate(const Point4& p) { state_[p.x][p.y][p.z][p.w] = false; }

  bool Valid(const Point4& p) {
    return p.x >= 0 && p.x < 20 && p.y >= 0 && p.y < 20 && p.z >= 0 &&
           p.z < 20 && p.w >= 0 && p.w < 20;
  }

  int ActiveNeighbors(const Point4& p) {
    int active_neighbors = 0;

    for (const int dx : {0, -1, 1}) {
      for (const int dy : {0, -1, 1}) {
        for (const int dz : {0, -1, 1}) {
          for (const int dw : {0, -1, 1}) {
            if (dx == 0 && dy == 0 && dz == 0 && dw == 0) {
              continue;
            }
            Point4 neighbor = {p.x + dx, p.y + dy, p.z + dz, p.w + dw};
            if (Valid(neighbor) && IsActive(neighbor)) {
              ++active_neighbors;
            }
          }
        }
      }
    }

    return active_neighbors;
  }

  int CountActive() const {
    int active = 0;
    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        for (int k = 0; k < 20; ++k) {
          for (int l = 0; l < 20; ++l) {
            if (IsActive(Point4{i, j, k, l})) {
              ++active;
            }
          }
        }
      }
    }
    return active;
  }

  void Simulate() {
    std::vector<Point4> to_activate, to_deactivate;

    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        for (int k = 0; k < 20; ++k) {
          for (int l = 0; l < 20; ++l) {
            int active_neighbors = ActiveNeighbors({i, j, k, l});
            if (IsActive({i, j, k, l}) &&
                !(active_neighbors == 2 || active_neighbors == 3)) {
              to_deactivate.push_back({i, j, k, l});
            }
            if (!IsActive({i, j, k, l}) && active_neighbors == 3) {
              to_activate.push_back({i, j, k, l});
            }
          }
        }
      }
    }

    std::cout << "Activating " << to_activate.size() << std::endl;
    for (const auto& p : to_activate) {
      Activate(p);
    }
    std::cout << "Deactivating " << to_deactivate.size() << std::endl;
    for (const auto& p : to_deactivate) {
      Deactivate(p);
    }
  }

 private:
  int rounds_;
  int board_;
  bool state_[20][20][20][20];
};

absl::StatusOr<int64_t> Cubes(const std::vector<std::string>& entries,
                              bool second) {
  if (!second) {
    Vasiona vasiona(entries.size() == 4 ? 4 : 7, entries);
    for (int i = 0; i < 6; ++i) {
      std::cout << "Simulation " << i + 1 << ", active "
                << vasiona.CountActive() << std::endl;
      vasiona.Simulate();
    }
    return vasiona.CountActive();
  }
  Vasiona4 vasiona(entries.size() == 4 ? 4 : 7, entries);
  for (int i = 0; i < 6; ++i) {
    std::cout << "Simulation " << i + 1 << ", active " << vasiona.CountActive()
              << std::endl;
    vasiona.Simulate();
  }
  return vasiona.CountActive();
}

