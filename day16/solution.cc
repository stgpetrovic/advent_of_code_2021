#include "day16/solution.h"

#include <bitset>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

namespace {

struct Criterion {
  int min;
  int max;
  bool operator()(int value) {
    auto result = value >= min && value <= max;
    std::cout << value << " matches [" << min << ", " << max << "] = " << result
              << std::endl;
    return result;
  }
};

class TicketOffice {
 public:
  void AddCriterion(const std::string field, Criterion criterion) {
    criteria_[field].push_back(criterion);
    std::cout << "Criterion for " << field << " [" << criterion.min << ", "
              << criterion.max << "]" << std::endl;
  }

  std::vector<std::string> MatchingCriteria(int value) const {
    std::vector<std::string> matching_criteria;
    for (const auto& it : criteria_) {
      if (absl::c_any_of(it.second,
                         [&value](Criterion c) { return c(value) == true; })) {
        matching_criteria.push_back(it.first);
      }
    }
    return matching_criteria;
  }

  void AddNearbyTicket(const std::string& numbers) {
    nearby_tickets_.push_back(ParseNumbers(numbers));
  }

  void SetMyTicket(const std::string& numbers) {
    my_ticket_ = ParseNumbers(numbers);
  }

  inline std::vector<int> GetMyTicket() const { return my_ticket_; }

  inline std::vector<std::vector<int>> NearbyTickets() const {
    return nearby_tickets_;
  }

  bool IsReal() const {
    for (const auto& it : criteria_) {
      if (absl::StartsWith(it.first, "departure")) {
        return true;
      }
    }
    return false;
  }

 private:
  std::vector<int> ParseNumbers(const std::string& numbers) {
    std::vector<int> v;
    for (const auto& number : absl::StrSplit(numbers, ",")) {
      int a;
      CHECK(absl::SimpleAtoi(number, &a));
      v.push_back(a);
    }
    return v;
  }

  absl::flat_hash_map<std::string, std::vector<Criterion>> criteria_;
  std::vector<std::vector<int>> nearby_tickets_;
  std::vector<int> my_ticket_;
};

}  // namespace

TicketOffice Parse(const std::vector<std::string>& entries) {
  TicketOffice ticket_office;

  int phase = 0;
  for (const auto& entry : entries) {
    if (entry.empty()) {
      continue;
    }
    if (entry == "your ticket:") {
      phase = 1;
      continue;
    }
    if (entry == "nearby tickets:") {
      phase = 2;
      continue;
    }

    if (phase == 0) {
      std::vector<std::string> rule = absl::StrSplit(entry, ": ");
      for (const auto& range : absl::StrSplit(rule[1], " or ")) {
        int min, max;
        std::vector<std::string> parts = absl::StrSplit(range, "-");
        CHECK(absl::SimpleAtoi(parts[0], &min));
        CHECK(absl::SimpleAtoi(parts[1], &max));
        ticket_office.AddCriterion(rule[0], Criterion{.min = min, .max = max});
      }
    }

    if (phase == 1) {
      ticket_office.SetMyTicket(entry);
    }

    if (phase == 2) {
      ticket_office.AddNearbyTicket(entry);
    }
  }

  return ticket_office;
}

int64_t CountFakeTickets(const std::vector<std::string>& entries) {
  int64_t sum = 0;
  TicketOffice ticket_office = Parse(entries);
  for (const auto& ticket : ticket_office.NearbyTickets()) {
    for (const auto& value : ticket) {
      absl::flat_hash_set<std::string> matches;
      for (const auto& match : ticket_office.MatchingCriteria(value)) {
        matches.insert(match);
      }
      if (matches.empty()) {
        sum += value;
      }
      std::cout << value << " mathches " << matches.size() << std::endl;
    }
  }
  return sum;
}

int64_t MyTicket(const std::vector<std::string>& entries) {
  TicketOffice ticket_office = Parse(entries);
  std::vector<std::vector<int>> tickets;
  for (const auto& ticket : ticket_office.NearbyTickets()) {
    bool valid = true;
    for (const auto& value : ticket) {
      absl::flat_hash_set<std::string> matches;
      for (const auto& match : ticket_office.MatchingCriteria(value)) {
        matches.insert(match);
      }
      if (matches.empty()) {
        valid = false;
      }
    }
    if (valid) {
      tickets.push_back(ticket);
    }
  }
  std::cout << "Valid tickets " << tickets.size() << std::endl;

  std::vector<std::vector<absl::flat_hash_set<std::string>>> t(tickets.size());
  for (int i = 0; i < tickets.size(); ++i) {
    t[i].resize(tickets[i].size());
    for (int j = 0; j < tickets[i].size(); ++j) {
      for (const auto& match : ticket_office.MatchingCriteria(tickets[i][j])) {
        t[i][j].insert(match);
      }
    }
  }

  absl::flat_hash_map<std::string, int> solution;
  std::vector<absl::flat_hash_set<std::string>> isec(tickets.size());

  for (int i = 0; i < t.size(); ++i) {
    isec[i] = t[0][i];
  }

  for (int i = 0; i < t.size(); ++i) {
    for (int j = 0; j < t[i].size(); ++j) {
      auto& m = isec[j];
      for (auto it = m.begin(), end = m.end(); it != end;) {
        auto pred = !t[i][j].contains(*it);
        auto copy_it = it++;
        if (pred) {
          m.erase(copy_it);
        }
      }
    }
  }

  for (int i = 0; i < isec.size(); ++i) {
    std::cout << i << ": " << absl::StrJoin(isec[i], ", ") << std::endl;
  }

  while (solution.size() != ticket_office.GetMyTicket().size()) {
    for (int i = 0; i < isec.size(); ++i) {
      absl::flat_hash_set<std::string> potential_solutions;
      for (const auto& field : isec[i]) {
        if (!solution.contains(field)) {
          potential_solutions.insert(field);
        }
      }
      if (potential_solutions.size() == 1) {
        std::cout << " solved " << i << " = " << *potential_solutions.begin()
                  << std::endl;
        solution[*potential_solutions.begin()] = i;
      }
    }
  }

  int64_t mul = 1;
  int64_t test_mul = 1;
  for (const auto& [field, value] : solution) {
    if (absl::StartsWith(field, "departure")) {
      mul *= ticket_office.GetMyTicket()[value];
    }
    test_mul *= ticket_office.GetMyTicket()[value];
  }
  if (mul == 1) {
    return test_mul;
  }
  return mul;
}

absl::StatusOr<int64_t> Chiketo(const std::vector<std::string>& entries,
                                bool second) {
  if (!second) {
    return CountFakeTickets(entries);
  }
  return MyTicket(entries);
}

