#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> Power(const std::vector<std::string>& input);
absl::StatusOr<int32_t> LifeSupport(const std::vector<std::string>& input);
