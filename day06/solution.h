#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<std::string> Spawn(const std::vector<std::string>& input,
                                  int64_t total_days);
