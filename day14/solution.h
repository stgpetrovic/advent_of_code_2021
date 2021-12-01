#include <bitset>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"

constexpr uint64_t k36Mask = 0xfffffffff;

class Machine {
 public:
  Machine();
  virtual ~Machine() = default;

  virtual void UpdateMask(const std::string& mask);

  virtual void SetMemory(int64_t address, std::bitset<36> value);

  virtual int64_t SumMemory() const;

 protected:
  std::bitset<36> mask_or_;
  std::bitset<36> mask_and_;
  absl::flat_hash_map<int64_t, std::bitset<36>> memory_;
};

class MachineV2 : public Machine {
 public:
  virtual void UpdateMask(const std::string& mask);

  virtual void SetMemory(int64_t address, std::bitset<36> value);

  virtual int64_t SumMemory() const;

 protected:
  absl::flat_hash_set<int> floating_;
};

absl::StatusOr<int64_t> Mask(const std::vector<std::string>& entries,
                             bool second = false);
