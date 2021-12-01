#include "day14/solution.h"

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

Machine::Machine() : mask_or_(0), mask_and_(0xffffffffffffffff) {
  std::cout << "masks: and " << mask_and_ << "    or " << mask_or_ << std::endl;
}

void Machine::UpdateMask(const std::string& mask) {
  for (int i = 0; i < mask.size(); ++i) {
    int offset = 35 - i;
    if (mask[i] == 'X') {
      mask_and_ |= 1UL << offset;
      mask_or_ &= ~(1UL << offset);
    } else if (mask[i] == '1') {
      mask_or_ |= 1UL << offset;
      mask_and_ |= 1UL << offset;
    } else if (mask[i] == '0') {
      mask_or_ &= ~(1UL << offset);
      mask_and_ &= ~(1UL << offset);
    }
  }
  std::cout << "masks: and " << mask_and_ << "    or " << mask_or_ << std::endl;
}

void Machine::SetMemory(int64_t address, std::bitset<36> value) {
  std::bitset<36> new_value = (value | mask_or_) & mask_and_;

  std::cout << "new value \n  " << value << std::endl
            << "| " << mask_or_ << std::endl
            << "& " << mask_and_ << std::endl
            << "  " << new_value << std::endl;
  std::cout << "Setting memory @" << address << " to " << new_value.to_ulong()
            << std::endl;
  memory_[address] = new_value;
}

int64_t Machine::SumMemory() const {
  int64_t sum = 0;
  for (const auto& it : memory_) {
    sum += it.second.to_ulong();
  }
  return sum;
}

// ------------------- V2 Machine -----------------------

void MachineV2::UpdateMask(const std::string& mask) {
  floating_.clear();
  for (int i = 0; i < mask.size(); ++i) {
    int offset = 35 - i;
    if (mask[i] == 'X') {
      floating_.insert(offset);
    } else if (mask[i] == '1') {
      mask_or_ |= 1UL << offset;
      mask_and_ |= 1UL << offset;
    } else if (mask[i] == '0') {
      mask_and_ |= 1UL << offset;
      mask_or_ &= ~(1UL << offset);
    }
  }
  std::cout << "masks: and " << mask_and_ << "    or " << mask_or_ << std::endl;
  std::cout << "floating bits " << absl::StrJoin(floating_, ", ") << std::endl;
}

int64_t MachineV2::SumMemory() const {
  int64_t sum = 0;
  for (const auto& it : memory_) {
    sum += it.second.to_ulong();
  }
  return sum;
}

void MachineV2::SetMemory(int64_t address, std::bitset<36> value) {
  auto new_address = (std::bitset<36>(address) | mask_or_) & mask_and_;
  for (int i = 0; i < std::pow(2, floating_.size()); ++i) {
    auto address_copy = new_address;
    std::bitset<36> binary_i(i);
    int j = 0;
    for (const auto& floating_bit : floating_) {
      address_copy[floating_bit] = binary_i[j++];
    }
    memory_[address_copy.to_ulong()] = value;
  }
}

int64_t RunMachine(const std::vector<std::string>& entries, bool second) {
  std::unique_ptr<Machine> machine;
  if (!second) {
    machine = absl::make_unique<Machine>();
  } else {
    machine = absl::make_unique<MachineV2>();
  }
  for (const auto& entry : entries) {
    std::vector<std::string> parts = absl::StrSplit(entry, " = ");
    std::cout << "command: " << entry << std::endl;
    if (parts[0] == "mask") {
      machine->UpdateMask(parts[1]);
    } else {
      int64_t address, value;
      CHECK(
          absl::SimpleAtoi(parts[0].substr(4, parts[0].size() - 5), &address));
      CHECK(absl::SimpleAtoi(parts[1], &value));
      machine->SetMemory(address, value);
    }
  }
  return machine->SumMemory();
}

absl::StatusOr<int64_t> Mask(const std::vector<std::string>& entries,
                             bool second) {
  return RunMachine(entries, second);
}

