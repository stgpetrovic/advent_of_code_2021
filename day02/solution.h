#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> ValidPasswords(const std::vector<std::string>& entries,
                                       int policy);
