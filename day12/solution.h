#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> Caves(const std::vector<std::string>& input);
absl::StatusOr<int64_t> CavesRepetition(const std::vector<std::string>& input);
