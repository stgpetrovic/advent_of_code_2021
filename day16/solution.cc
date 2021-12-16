#include "day16/solution.h"

#include <glog/logging.h>

#include <bitset>
#include <cstdint>
#include <iostream>
#include <sstream>
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

class Packet {
 public:
  explicit Packet(short version) : version_(version) {}
  explicit Packet(short version, const std::vector<Packet*> children)
      : version_(version), children_(std::move(children)) {}

  virtual ~Packet() {
    for (const auto& child : children_) {
      delete child;
    }
  }

  virtual int64_t Value() const {
    int64_t total = 0;
    for (const auto& child : children_) {
      total += child->Value();
    }
    return total;
  }

  virtual int64_t SumVersions() const {
    int64_t total = version_;
    for (const auto& child : children_) {
      total += child->SumVersions();
    }
    return total;
  }

 protected:
  short version_;
  std::vector<Packet*> children_;
};

class Literal : public Packet {
 public:
  Literal(short version, int64_t value) : Packet(version), value_(value) {}

  int64_t Value() const override { return value_; }

 protected:
  int64_t value_;
};

class Operator : public Packet {
 public:
  Operator(short version, short type_id, const std::vector<Packet*>& children)
      : Packet(version, std::move(children)), type_id_(type_id) {}

  int64_t Value() const override {
    switch (type_id_) {
      case 0: {
        int64_t total = 0;
        for (const auto& child : children_) {
          total += child->Value();
        }
        return total;
      }
      case 1: {
        int64_t total = 1;
        for (const auto& child : children_) {
          total *= child->Value();
        }
        return total;
      }
      case 2: {
        std::vector<int64_t> values;
        for (const auto& child : children_) {
          values.push_back(child->Value());
        }
        return *absl::c_min_element(values);
      };
      case 3: {
        std::vector<int64_t> values;
        for (const auto& child : children_) {
          values.push_back(child->Value());
        }
        return *absl::c_max_element(values);
      };
      case 5: {
        int64_t l = children_[0]->Value();
        int64_t r = children_[1]->Value();
        return l > r ? 1 : 0;
      };
      case 6: {
        int64_t l = children_[0]->Value();
        int64_t r = children_[1]->Value();
        return l < r ? 1 : 0;
      };
      case 7: {
        int64_t l = children_[0]->Value();
        int64_t r = children_[1]->Value();
        return l == r ? 1 : 0;
      };
    }
    LOG(FATAL) << "Nidje veze";
  }

 protected:
  short type_id_;
};

int64_t BinToDec(absl::string_view binary) {
  return std::stol(std::string(binary), 0, 2);
}

int64_t ConsumeZeros(absl::string_view code, int64_t n) {
  int64_t i = 0;
  while (i % 4 != 0 && i < code.length() && i < 4 && code.substr(n)[i] == '0') {
    ++i;
  }
  return i;
}

std::pair<int64_t, size_t> ParseLiteral(absl::string_view code, size_t offset) {
  int i = offset;
  bool done = false;
  std::string binary;

  while (!done) {
    if (code[i] == '0') {
      done = true;
    }
    ++i;

    bool started = false;
    for (int j = 0; j < 4; ++j) {
      if (i < 5 && !started && code[i + j] == '0') {
        continue;
      }
      binary += code[i + j];
      started = true;
    }
    i += 4;
  }
  i += ConsumeZeros(code, i);

  return std::make_pair(BinToDec(binary), i);
}

std::pair<int64_t, size_t> ParseN(absl::string_view code, size_t offset,
                                  int64_t n) {
  return std::make_pair(BinToDec(code.substr(offset, n)), n);
}

std::pair<std::vector<Packet*>, int64_t> Parse(absl::string_view program,
                                               int64_t max = -1) {
  std::vector<Packet*> elements;

  int64_t version, type;
  int64_t i = 0;
  while (i + 8 < program.size()) {
    LOG(INFO) << " i = " << i << ", len = " << program.size();
    LOG(INFO) << "Parsing " << program.substr(i);
    if (max > 0 && elements.size() == max) {
      return std::make_pair(elements, i);
    }
    if (i < 0 ||
        absl::c_count(program.substr(i), '0') == program.length() - i) {
      break;
    }

    auto res = ParseN(program, i, 3);
    version = res.first;
    i += res.second;
    LOG(INFO) << "\tVersion " << res.first << " offset " << i;
    res = ParseN(program, i, 3);
    type = res.first;
    i += res.second;
    LOG(INFO) << "\tType " << (res.first == 4 ? "LITERAL" : "OPERATOR")
              << " offset " << i;
    if (type == 4) {  // Literal value
      res = ParseLiteral(program, i);
      i = res.second;
      LOG(INFO) << "\tLiteral " << res.first << " offset " << i;
      elements.push_back(new Literal(version, res.first));
    } else {  // Operator
      auto res = ParseN(program, i, 1);
      i += res.second;
      LOG(INFO) << "\tType length ID " << res.first << " offset " << i;
      if (res.first == 0) {  // length is a 15-bit number length in bits
        auto res = ParseN(program, i, 15);
        i += res.second;
        LOG(INFO) << "\tLength bits " << res.first << " offset " << i;
        auto pkgs = Parse(program.substr(i, res.first));
        i += res.first;
        elements.push_back(new Operator(version, type, pkgs.first));
      } else if (res.first == 1) {  // length is a 11-bit number of packets
        auto res = ParseN(program, i, 11);
        i += res.second;
        LOG(INFO) << "\tLength package: " << res.first << " offset " << i;
        auto pkgs = Parse(program.substr(i), res.first);
        i += pkgs.second;
        elements.push_back(new Operator(version, type, pkgs.first));
      }
    }
  }

  if (max > 0 && elements.size() == max) {
    return std::make_pair(elements, i);
  }

  return std::make_pair(elements, -1);
}

std::vector<Packet*> ParseHex(absl::string_view code) {
  std::string program;
  for (const auto& hex : code) {
    std::stringstream ss;
    ss << std::hex << hex;
    unsigned n;
    ss >> n;
    std::bitset<4> b(n);
    absl::StrAppend(&program, b.to_string());
  }
  return Parse(program).first;
}

}  // namespace

absl::StatusOr<int64_t> VersionSum(const std::vector<std::string>& input) {
  int64_t total = 0;
  for (const auto& child : ParseHex(input[0])) {
    total += child->SumVersions();
  }
  return total;
}

absl::StatusOr<int64_t> Eval(const std::vector<std::string>& input) {
  int64_t total = 0;
  for (const auto& child : ParseHex(input[0])) {
    total += child->Value();
  }
  return total;
}
