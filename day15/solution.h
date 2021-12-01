#include <bitset>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"

absl::StatusOr<int64_t> Numbers(const std::vector<int>& entries,
                                bool second = false);
