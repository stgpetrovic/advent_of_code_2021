#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> Spawn(const std::vector<std::string>& input,
                                  int64_t total_days);
