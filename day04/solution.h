#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> Bingo(const std::vector<std::string>& input);
absl::StatusOr<int32_t> BingoLose(const std::vector<std::string>& input);
