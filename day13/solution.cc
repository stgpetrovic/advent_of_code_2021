#include "day13/solution.h"

#include <memory>
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

int64_t FirstBus(int64_t t, const std::vector<int64_t> periods) {
  int best_bus_id = -1;
  int min_wait = 10000000;
  for (const auto& period : periods) {
    if ((period - t % period) < min_wait) {
      min_wait = period - t % period;
      best_bus_id = period;
      std::cout << "Found better bus: id = " << period << "; t mod period "
                << min_wait << std::endl;
    }
  }
  return (best_bus_id - t % (best_bus_id)) * best_bus_id;
}

long long MultiplicativeModularInverse(int64_t a, int64_t b) {
  int64_t b0 = b;
  int64_t t = 0;
  int64_t q = 0;
  int64_t x0 = 0;
  int64_t x1 = 1;

  if (b == 1) {
    return 1;
  }

  while (a > 1) {
    q = a / b;
    t = b;
    b = a % b;
    a = t;
    t = x0;
    x0 = x1 - q * x0;
    x1 = t;
  }

  if (x1 < 0) {
    x1 += b0;
  }

  return x1;
}

unsigned long long SecondBus(const std::vector<int64_t> periods) {
  absl::flat_hash_map<int, int> n_to_r;

  unsigned long long M = 1;
  std::vector<unsigned long long> m(periods.size());
  for (int i = 0; i < periods.size(); ++i) {
    if (periods[i] == -1) continue;
    M *= periods[i];
  }
  for (int i = 0; i < periods.size(); ++i) {
    if (periods[i] == -1) continue;
    m[i] = (M / periods[i]);
  }
  unsigned long long Y = 0;
  for (int i = 0; i < periods.size(); ++i) {
    if (periods[i] == -1) continue;
    Y += ((periods[i] - i) % periods[i]) * m[i] *
         MultiplicativeModularInverse(m[i], periods[i]);
  }
  return Y % M;
}

}  // namespace

absl::StatusOr<unsigned long long> Bus(const std::vector<std::string>& entries,
                                       bool second) {
  int64_t t;
  CHECK(absl::SimpleAtoi(entries[0], &t));
  std::vector<int64_t> periods;
  for (const auto& period : absl::StrSplit(entries[1], ',')) {
    if (period == "x") {
      if (second) {
        periods.push_back(-1);
      }
      continue;
    }
    int64_t t;
    CHECK(absl::SimpleAtoi(period, &t));
    periods.push_back(t);
  }
  std::cout << "Timestamp " << t << std::endl;
  std::cout << "Periods " << absl::StrJoin(periods, ", ") << std::endl;

  if (!second) {
    return FirstBus(t, periods);
  }
  return SecondBus(periods);
}

