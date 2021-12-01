#include "day12/solution.h"

#include <memory>
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

SlonovBrodElan40Stopa::SlonovBrodElan40Stopa() : x_(0), y_(0), heading_(EAST) {}

void SlonovBrodElan40Stopa::SetSail(Action action, int value) {
  switch (action) {
    case N:
      GoY(value);
      break;
    case S:
      GoY(-value);
      break;
    case E:
      GoX(value);
      break;
    case W:
      GoX(-value);
      break;
    case L:
      Port(value);
      break;
    case R:
      Starboard(value);
      break;
    case F:
      Forward(value);
      break;
  }
}

void SlonovBrodElan40Stopa::Port(int angle) {
  for (int i = 0; i < angle / 90; ++i) {
    switch (heading_) {
      case EAST:
        heading_ = NORTH;
        break;
      case SOUTH:
        heading_ = EAST;
        break;
      case WEST:
        heading_ = SOUTH;
        break;
      case NORTH:
        heading_ = WEST;
        break;
    }
  }
}

void SlonovBrodElan40Stopa::Starboard(int angle) {
  for (int i = 0; i < angle / 90; ++i) {
    switch (heading_) {
      case EAST:
        heading_ = SOUTH;
        break;
      case SOUTH:
        heading_ = WEST;
        break;
      case WEST:
        heading_ = NORTH;
        break;
      case NORTH:
        heading_ = EAST;
        break;
    }
  }
}

void SlonovBrodElan40Stopa::GoX(int value) { x_ += value; }

void SlonovBrodElan40Stopa::GoY(int value) { y_ += value; }

void SlonovBrodElan40Stopa::Forward(int value) {
  std::pair<int, int> d = {0, 0};
  switch (heading_) {
    case EAST:
      d = {1, 0};
      break;
    case SOUTH:
      d = {0, -1};
      break;
    case WEST:
      d = {-1, 0};
      break;
    case NORTH:
      d = {0, 1};
      break;
  }
  x_ += value * d.first;
  y_ += value * d.second;
}

int SlonovBrodElan40Stopa::Distance() { return std::abs(x_) + std::abs(y_); }

// Waypoint-nagivated boat.
WaypointSlonovBrodElan40Stopa::WaypointSlonovBrodElan40Stopa()
    : SlonovBrodElan40Stopa(), waypoint_({10, 1}) {}

void WaypointSlonovBrodElan40Stopa::Forward(int value) {
  x_ += value * waypoint_.first;
  y_ += value * waypoint_.second;
}

int Quandrant(int i, int j) {
  if (i >= 0 && j >= 0) return 1;
  if (i >= 0 && j <= 0) return 2;
  if (i <= 0 && j <= 0) return 3;
  return 4;
}

void RotateCcw(std::pair<int, int>* p) {
  int t = p->first;
  p->first = -1 * p->second;
  p->second = t;
}

void RotateCw(std::pair<int, int>* p) {
  int t = p->first;
  p->first = p->second;
  p->second = -1 * t;
}

void WaypointSlonovBrodElan40Stopa::Port(int value) {
  for (int i = 0; i < value / 90; ++i) {
    RotateCcw(&waypoint_);
  }
}

void WaypointSlonovBrodElan40Stopa::Starboard(int value) {
  for (int i = 0; i < value / 90; ++i) {
    RotateCw(&waypoint_);
  }
}

void WaypointSlonovBrodElan40Stopa::GoX(int value) { waypoint_.first += value; }

void WaypointSlonovBrodElan40Stopa::GoY(int value) {
  waypoint_.second += value;
}

Action ParseAction(char a) {
  if (a == 'N') return N;
  if (a == 'S') return S;
  if (a == 'E') return E;
  if (a == 'W') return W;
  if (a == 'L') return L;
  if (a == 'R') return R;
  if (a == 'F') return F;
  CHECK(0);  // invalid input
}

int Distance(const std::vector<std::string>& entries, bool waypoint) {
  std::unique_ptr<SlonovBrodElan40Stopa> kraljica_jelena;
  if (!waypoint) {
    kraljica_jelena = absl::make_unique<SlonovBrodElan40Stopa>();
  } else {
    kraljica_jelena = absl::make_unique<WaypointSlonovBrodElan40Stopa>();
  }

  for (const auto& entry : entries) {
    Action action = ParseAction(entry[0]);
    int value;
    CHECK(absl::SimpleAtoi(entry.substr(1), &value));
    kraljica_jelena->SetSail(action, value);
  }
  return kraljica_jelena->Distance();
}

absl::StatusOr<int64_t> Sail(const std::vector<std::string>& entries,
                             bool second) {
  return Distance(entries, second);
}

