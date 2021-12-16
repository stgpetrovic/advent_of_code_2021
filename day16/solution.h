#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> VersionSum(const std::vector<std::string>& input);
absl::StatusOr<int64_t> Eval(const std::vector<std::string>& input);
