#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> Clock(const std::vector<std::string>& input);
absl::StatusOr<int32_t> ClockSum(const std::vector<std::string>& input);
