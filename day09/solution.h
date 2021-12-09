#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> RiskLevels(const std::vector<std::string>& input);
absl::StatusOr<int32_t> Basins(const std::vector<std::string>& input);
