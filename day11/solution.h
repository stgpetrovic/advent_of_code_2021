#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> DumboFlashes(const std::vector<std::string>& input);
absl::StatusOr<int64_t> DumboSync(const std::vector<std::string>& input);
