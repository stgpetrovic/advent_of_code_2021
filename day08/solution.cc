#include "day08/solution.h"

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

namespace {

class SlonCpu {
 public:
  SlonCpu(const SlonCpu&) = delete;
  SlonCpu operator=(const SlonCpu&) = delete;
  SlonCpu(const SlonCpu&&) = delete;
  SlonCpu operator=(const SlonCpu&&) = delete;

  explicit SlonCpu(const std::vector<std::string> code)
      : code_(code), acc_(0), pc_(0) {}

  absl::Status Run(bool exit_on_loop = true) {
    pc_ = 0;
    while (pc_ < code_.size()) {
      if (executed_instructions_.contains(pc_)) {
        return absl::InvalidArgumentError(
            absl::StrCat("loop; reexecuting instruction at: ", pc_));
      }
      executed_instructions_.insert(pc_);
      const auto& [opcode, arg] = ParseInstruction(code_[pc_]);
      std::cout << "exec\t" << opcode << " " << arg << std::endl;
      if (opcode == "nop") {
        ++pc_;
      } else if (opcode == "acc") {
        acc_ += arg;
        ++pc_;
      } else if (opcode == "jmp") {
        pc_ += arg;
      }
    }
    return absl::OkStatus();
  }

  inline int32_t Acc() { return acc_; }

 private:
  std::pair<std::string, int32_t> ParseInstruction(
      const std::string& instruction) const {
    const std::vector<std::string> parts = absl::StrSplit(instruction, ' ');
    int32_t argument;
    CHECK(absl::SimpleAtoi(parts[1], &argument));
    return std::make_pair(parts[0], argument);
  }

  std::vector<std::string> code_;
  absl::flat_hash_set<int32_t> executed_instructions_;
  int32_t acc_;
  int32_t pc_;
};

std::vector<std::vector<std::string>> Mutate(
    const std::vector<std::string>& code) {
  std::vector<std::vector<std::string>> mutants;
  mutants.push_back(code);
  for (int i = 0; i < code.size(); ++i) {
    if (absl::StartsWith(code[i], "nop")) {
      auto mutant = code;
      mutant[i] = absl::StrCat("jmp", mutant[i].substr(3));
      mutants.push_back(mutant);
    } else if (absl::StartsWith(code[i], "jmp")) {
      auto mutant = code;
      mutant[i] = absl::StrCat("nop", mutant[i].substr(3));
      mutants.push_back(mutant);
    }
  }
  return mutants;
}

}  // namespace

#define CHECK(EXPRESSION)                           \
  if (!EXPRESSION) {                                \
    std::cerr << "check fail in line " << __LINE__; \
    exit(1);                                        \
  }

absl::StatusOr<int64_t> Parse(const std::vector<std::string>& entries,
                              bool second) {
  // First.
  if (!second) {
    SlonCpu slon_cpu(entries);
    slon_cpu.Run().IgnoreError();
    return slon_cpu.Acc();
  }

  // Second.
  for (const auto& mutant_code : Mutate(entries)) {
    SlonCpu slon_cpu(mutant_code);
    if (slon_cpu.Run().ok()) {
      return slon_cpu.Acc();
    }
  }
  return absl::InvalidArgumentError("no code version terminates.");
}

