#include "day11/solution.h"

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

bool InRange(const std::vector<std::string>& entries, int i, int j) {
  return !(i < 0 || j < 0 || i >= entries.size() || j >= entries[i].size());
}

bool Empty(const std::vector<std::string>& entries, int i, int j) {
  if (!InRange(entries, i, j)) {
    return true;
  }
  return entries[i][j] != '#';
}

bool EmptyInDirection(const std::vector<std::string>& entries, int i, int j,
                      int di, int dj) {
  i += di;
  j += dj;
  while (InRange(entries, i, j)) {
    if (entries[i][j] == '.') {
      i += di;
      j += dj;
      continue;
    }
    return entries[i][j] != '#';
  }
  return true;
}

int CountAdjacentFree(const std::vector<std::string>& entries, int i, int j,
                      bool second) {
  if (!second) {
    int l = Empty(entries, i, j - 1) ? 1 : 0;
    int r = Empty(entries, i, j + 1) ? 1 : 0;
    int u = Empty(entries, i - 1, j) ? 1 : 0;
    int d = Empty(entries, i + 1, j) ? 1 : 0;
    int ul = Empty(entries, i - 1, j - 1) ? 1 : 0;
    int dr = Empty(entries, i + 1, j + 1) ? 1 : 0;
    int dl = Empty(entries, i + 1, j - 1) ? 1 : 0;
    int ur = Empty(entries, i - 1, j + 1) ? 1 : 0;
    return l + r + u + d + ul + ur + dl + dr;
  }
  int l = EmptyInDirection(entries, i, j, 0, -1) ? 1 : 0;
  int r = EmptyInDirection(entries, i, j, 0, 1) ? 1 : 0;
  int u = EmptyInDirection(entries, i, j, -1, 0) ? 1 : 0;
  int d = EmptyInDirection(entries, i, j, 1, 0) ? 1 : 0;
  int ul = EmptyInDirection(entries, i, j, -1, -1) ? 1 : 0;
  int dr = EmptyInDirection(entries, i, j, 1, 1) ? 1 : 0;
  int dl = EmptyInDirection(entries, i, j, 1, -1) ? 1 : 0;
  int ur = EmptyInDirection(entries, i, j, -1, 1) ? 1 : 0;
  return l + r + u + d + ul + ur + dl + dr;
}

bool AllAdjancentFree(const std::vector<std::string>& entries, int i, int j,
                      bool second) {
  return CountAdjacentFree(entries, i, j, second) == 8;
}

int CountOccupied(const std::vector<std::string>& entries) {
  int occupied = 0;
  for (int i = 0; i < entries.size(); ++i) {
    for (int j = 0; j < entries[i].size(); ++j) {
      if (entries[i][j] == '#') {
        ++occupied;
      }
    }
  }
  return occupied;
}

void PrintSeatPlan(const std::vector<std::string>& entries) {
  std::cout << std::endl;
  for (int i = 0; i < entries.size(); ++i) {
    std::cout << entries[i] << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

int64_t SimulateWorld(std::vector<std::string>& entries, bool second) {
  absl::flat_hash_set<std::pair<int, int>> occupy;
  absl::flat_hash_set<std::pair<int, int>> vacate;
  for (int i = 0; i < entries.size(); ++i) {
    for (int j = 0; j < entries[i].size(); ++j) {
      if (entries[i][j] == 'L' && AllAdjancentFree(entries, i, j, second)) {
        occupy.insert({i, j});
      }
      if (entries[i][j] == '#' &&
          CountAdjacentFree(entries, i, j, second) <= (second ? 3 : 4)) {
        vacate.insert({i, j});
      }
    }
  }
  PrintSeatPlan(entries);
  for (const auto& [i, j] : occupy) {
    entries[i][j] = '#';
  }
  for (const auto& [i, j] : vacate) {
    entries[i][j] = 'L';
  }
  return occupy.size() + vacate.size();
}

int64_t CountSeats(std::vector<std::string>& entries, bool second) {
  while (SimulateWorld(entries, second))
    ;
  return CountOccupied(entries);
}

}  // namespace

absl::StatusOr<int64_t> Seats(const std::vector<std::string>& entries,
                              bool second) {
  auto entries_copy = entries;
  return CountSeats(entries_copy, second);
}

