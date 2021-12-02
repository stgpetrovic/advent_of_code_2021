#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> Navigate(const std::vector<std::string>& input);
absl::StatusOr<int32_t> NavigateWithAim(const std::vector<std::string>& input);
