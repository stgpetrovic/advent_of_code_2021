#include "day07/solution.h"

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

#define INF 0x3f3f3f3f

namespace {
using ipair = std::pair<int, int>;

class Graph {
 public:
  explicit Graph(int V) {
    this->V = V;
    adj = new std::list<ipair>[V];
  }

  void AddEdge(int u, int v, int w) { adj[u].push_back(std::make_pair(v, w)); }

  std::vector<ipair> ShortestPaths(int src) {
    std::priority_queue<ipair, std::vector<ipair>, std::greater<ipair> > pq;
    std::vector<int> dist(V, INF);

    pq.push(std::make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      for (const auto& [v, weight] : adj[u]) {
        if (dist[v] > dist[u] + weight) {
          dist[v] = dist[u] + weight;
          pq.push(std::make_pair(dist[v], v));
        }
      }
    }
    std::vector<ipair> distances;
    for (int i = 0; i < V; ++i) {
      distances.push_back({i, dist[i]});
    }
    return distances;
  }

  int TotalBags(int src) {
    std::stack<ipair> s;
    s.push(std::make_pair(src, 1));

    int total_bags = 0;
    while (!s.empty()) {
      int u = s.top().first;
      int w = s.top().second;
      total_bags += w;
      s.pop();
      for (const auto& [v, weight] : adj[u]) {
        s.push(std::make_pair(v, w * weight));
      }
    }
    return total_bags - 1;  // initial is not counted
  }

 private:
  int V;

  std::list<ipair>* adj;
};

struct Rule {
  std::string source_bag;
  std::string destination_bag;
  int count;

  static std::vector<Rule> FromText(const std::string& rule_text) {
    std::vector<std::string> parts =
        absl::StrSplit(rule_text, " bags contain ");

    if (absl::StrContains(parts[1], "no other bags")) {
      return {};
    }

    std::vector<Rule> rules;

    std::vector<std::string> destination_parts = absl::StrSplit(parts[1], ", ");
    for (const auto& dp : destination_parts) {
      Rule rule;
      rule.source_bag = parts[0];
      std::vector<std::string> inner = absl::StrSplit(dp, " ");
      CHECK(absl::SimpleAtoi(inner[0], &rule.count));
      rule.destination_bag = absl::StrCat(inner[1], " ", inner[2]);
      rules.push_back(rule);
    }

    return rules;
  }
};

}  // namespace

absl::StatusOr<int64_t> Bags(const std::vector<std::string>& entries,
                             bool second) {
  int reachable = 0;
  int total_bags = 0;
  absl::flat_hash_map<std::string, int> name_to_id;

  auto GetId = [&total_bags, &name_to_id](const std::string& name) {
    if (!name_to_id.contains(name)) {
      name_to_id[name] = total_bags;
      ++total_bags;
    }
    return name_to_id[name];
  };

  std::vector<Rule> rules;
  for (const auto& entry : entries) {
    for (const auto& rule : Rule::FromText(entry)) {
      rules.push_back(rule);
    }
  }
  Graph g(rules.size());
  for (const auto& rule : rules) {
    g.AddEdge(GetId(rule.source_bag), GetId(rule.destination_bag), rule.count);
  }

  // First.
  if (!second) {
    for (const auto& [bag_name, bag_id] : name_to_id) {
      auto paths = g.ShortestPaths(bag_id);
      for (const auto& [node, cost] : paths) {
        if (bag_id == node) {
          continue;
        }
        if (node == GetId("shiny gold") && cost != INF) {
          ++reachable;
        }
      }
    }
    return reachable;
  }

  // Second.
  return g.TotalBags(GetId("shiny gold"));
}

