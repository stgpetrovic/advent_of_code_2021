#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> FindExit(const std::vector<std::string>& input,
                                 bool large);
