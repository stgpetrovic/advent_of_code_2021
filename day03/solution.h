#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"

using Point = std::pair<size_t, size_t>;

class MutatedForest {
 public:
  MutatedForest(const MutatedForest&) = delete;
  MutatedForest operator=(const MutatedForest&) = delete;
  explicit MutatedForest(const std::vector<std::string>& entries);

  bool IsTree(size_t i, size_t j) const;

 private:
  absl::flat_hash_set<Point> trees_;
  int width_;
};

absl::StatusOr<int64_t> CountTrees(const std::vector<std::string>& entries,
                                   const std::vector<Point>& slope);
