#include "day12/solution.h"

#include <glog/logging.h>

#include <cstdint>
#include <stack>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

namespace {

class Matrix {
 public:
  explicit Matrix(const std::vector<std::string>& lines)
      : adj_{std::vector<int32_t>()}, max_id_(0) {
    for (int i = 0; i < lines.size(); ++i) {
      std::vector<std::string> parts = absl::StrSplit(lines[i], '-');
      CHECK_EQ(parts.size(), 2) << "parts not size 2: " << parts.size();
      const auto& id_left = NodeId(parts[0]);
      const auto& id_right = NodeId(parts[1]);
      if (adj_.size() <= std::max(id_left, id_right)) {
        adj_.resize(2 * std::max(id_left, id_right));
      }
      adj_[id_left].push_back(id_right);
      adj_[id_right].push_back(id_left);
    }
    adj_.resize(max_id_);
  }

  struct State {
    int32_t node;
    int32_t repeatable_id;
    std::vector<bool> visited;
    std::vector<int32_t> path;
  };

  void Dfs(int32_t repeatable_id, std::vector<std::string>* paths) {
    std::stack<State> s;
    s.push({.node = start_id_,
            .repeatable_id = repeatable_id,
            .visited = std::vector<bool>(max_id_)});

    while (!s.empty()) {
      State p = s.top();
      s.pop();
      p.visited[p.node] = true;

      std::vector<int32_t> new_path(p.path);
      new_path.push_back(p.node);

      if (p.node == end_id_) {
        paths->push_back(absl::StrJoin(new_path, "->"));
        continue;
      }

      auto can_visit = [this](const State& s, int32_t i) {
        return IsLarge(i) || !s.visited[i];
      };

      for (const auto& adj : adj_[p.node]) {
        if (can_visit(p, adj)) {
          s.push({.node = adj,
                  .repeatable_id = p.repeatable_id,
                  .visited = p.visited,
                  .path = new_path});
        } else if (adj == p.repeatable_id && p.visited[adj]) {
          s.push({.node = adj,
                  .repeatable_id = -1,  // can't revisit again
                  .visited = p.visited,
                  .path = new_path});
        }
      }
    }
  }

  std::vector<std::string> UniquePaths(int32_t repeatable_id) {
    std::vector<std::string> paths;
    Dfs(repeatable_id, &paths);
    return paths;
  }

  int32_t UniquePathsOneSmallRepetition() {
    absl::flat_hash_set<std::string> paths;
    for (const auto& [id, name] : names_) {
      if (IsSmall(id) && id != start_id_ && id != end_id_) {
        absl::c_copy(UniquePaths(id), std::inserter(paths, paths.begin()));
      }
    }
    return paths.size();
  }

 private:
  int32_t NodeId(const std::string& name) {
    if (auto it = idx_.find(name); it != idx_.end()) {
      return it->second;
    }
    idx_.insert({name, max_id_});
    if (name == "start") {
      start_id_ = max_id_;
    } else if (name == "end") {
      end_id_ = max_id_;
    }
    if (std::isupper(name[0])) {
      large_.insert(max_id_);
    }
    names_[max_id_] = name;
    return max_id_++;
  }

  inline bool IsLarge(int32_t id) { return large_.contains(id); }
  inline bool IsSmall(int32_t id) { return !large_.contains(id); }
  inline std::string Name(int32_t id) { return names_[id]; }

  std::vector<std::vector<int32_t>> adj_;
  absl::flat_hash_map<std::string, int32_t> idx_;
  absl::flat_hash_set<int32_t> large_;
  absl::flat_hash_map<int32_t, std::string> names_;
  int32_t max_id_;
  int32_t start_id_, end_id_;
};

}  // namespace

absl::StatusOr<int64_t> Caves(const std::vector<std::string>& input) {
  Matrix matrix(input);
  return matrix.UniquePaths(/*repeatable_id=*/-1).size();
}

absl::StatusOr<int64_t> CavesRepetition(const std::vector<std::string>& input) {
  Matrix matrix(input);
  return matrix.UniquePathsOneSmallRepetition();
}
