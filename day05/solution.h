#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int32_t> DangerousFumes(const std::vector<std::string>& input,
                                       bool consider_diagonals = false);
