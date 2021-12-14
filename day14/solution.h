#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> Polymer(const std::vector<std::string>& input,
                                int64_t steps);
