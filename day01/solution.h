#include "absl/status/statusor.h"
#include "absl/container/flat_hash_set.h"

absl::StatusOr<int32_t> TwoSumsTo2020(const absl::flat_hash_set<int32_t>& numbers);
absl::StatusOr<int32_t> ThreeSumsTo2020(const absl::flat_hash_set<int32_t>& numbers);
