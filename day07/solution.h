#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> Crevetten(const std::vector<std::string>& input,
                                  bool acc = false);
