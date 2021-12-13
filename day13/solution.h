#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> Fold(const std::vector<std::string>& input);
absl::StatusOr<int32_t> CameraCode(const std::vector<std::string>& input);
