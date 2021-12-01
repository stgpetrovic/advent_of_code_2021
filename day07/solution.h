#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"

absl::StatusOr<int64_t> Bags(const std::vector<std::string>& entries,
                            bool second = false);
