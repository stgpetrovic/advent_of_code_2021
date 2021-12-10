#include <string>
#include <vector>

#include "absl/status/statusor.h"

absl::StatusOr<int64_t> SyntaxScore(const std::vector<std::string>& input);
absl::StatusOr<int64_t> AutocompleteScore(
    const std::vector<std::string>& input);
