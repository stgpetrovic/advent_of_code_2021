#include "day02/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <string>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

namespace {

enum Direction { FORWARD = 0, DOWN = 1, UP = 2 };

struct Instruction {
  Direction direction;
  int32_t distance;
};

absl::StatusOr<std::vector<Instruction>> Parse(
    const std::vector<std::string>& input) {
  std::vector<Instruction> instructions;

  for (const auto& line : input) {
    std::vector<std::string> parts = absl::StrSplit(line, ' ');
    int32_t distance;
    if (!absl::SimpleAtoi(parts[1], &distance)) {
      return absl::InvalidArgumentError(
          absl::StrCat("cannot parse distance: ", parts[1]));
    }
    Direction direction;
    if (parts[0] == "forward") {
      direction = Direction::FORWARD;
    } else if (parts[0] == "up") {
      direction = Direction::UP;
    } else if (parts[0] == "down") {
      direction = Direction::DOWN;
    } else {
      return absl::InvalidArgumentError(
          absl::StrCat("cannot parse direction: ", parts[0]));
    }
    instructions.push_back({.direction = direction, .distance = distance});
  }

  return instructions;
}

struct Position {
  int32_t x;
  int32_t y;
  int32_t aim;
  int32_t Hash() { return x * y; }
};

}  // namespace

absl::StatusOr<int32_t> Navigate(const std::vector<std::string>& input) {
  auto instructions = Parse(input);
  if (!instructions.ok()) {
    return instructions.status();
  }
  Position position{.x = 0, .y = 0};
  for (const auto& instruction : *instructions) {
    switch (instruction.direction) {
      case FORWARD:
        position.x += instruction.distance;
        break;
      case UP:
        position.y -= instruction.distance;
        break;
      case DOWN:
        position.y += instruction.distance;
        break;
    }
  }
  return position.Hash();
}

absl::StatusOr<int32_t> NavigateWithAim(const std::vector<std::string>& input) {
  auto instructions = Parse(input);
  if (!instructions.ok()) {
    return instructions.status();
  }
  Position position{.x = 0, .y = 0, .aim = 0};
  for (const auto& instruction : *instructions) {
    switch (instruction.direction) {
      case FORWARD:
        position.x += instruction.distance;
        position.y += position.aim * instruction.distance;
        break;
      case UP:
        position.aim -= instruction.distance;
        break;
      case DOWN:
        position.aim += instruction.distance;
        break;
    }
  }
  return position.Hash();
}
