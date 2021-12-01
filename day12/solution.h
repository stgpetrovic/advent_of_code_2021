#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"

enum Heading { EAST = 0, SOUTH, WEST, NORTH };

enum Action { N = 0, S, E, W, L, R, F };

class SlonovBrodElan40Stopa {
 public:
  SlonovBrodElan40Stopa(const SlonovBrodElan40Stopa&) = delete;
  SlonovBrodElan40Stopa operator=(const SlonovBrodElan40Stopa&) = delete;
  SlonovBrodElan40Stopa(const SlonovBrodElan40Stopa&&) = delete;
  SlonovBrodElan40Stopa operator=(const SlonovBrodElan40Stopa&&) = delete;
  SlonovBrodElan40Stopa();
  virtual ~SlonovBrodElan40Stopa() = default;

  virtual void SetSail(Action action, int value);

  int Distance();

 protected:
  virtual void Forward(int value);
  virtual void Port(int angle);
  virtual void Starboard(int angle);
  virtual void GoX(int value);
  virtual void GoY(int value);

  int x_, y_;
  Heading heading_;
};

class WaypointSlonovBrodElan40Stopa : public SlonovBrodElan40Stopa {
 public:
  WaypointSlonovBrodElan40Stopa();

 protected:
  virtual void Forward(int value);
  virtual void Port(int angle);
  virtual void Starboard(int angle);
  virtual void GoX(int value);
  virtual void GoY(int value);

  std::pair<int, int> waypoint_;
};

absl::StatusOr<int64_t> Sail(const std::vector<std::string>& entries,
                             bool second = false);
