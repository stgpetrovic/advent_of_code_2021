#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/status/statusor.h"
#include "day04/solution.h"

ABSL_FLAG(std::string, in_file, "", "file with input data");
ABSL_FLAG(bool, second_part, false, "whether to run the 2nd part");

std::vector<std::string> ReadInput() {
  std::vector<std::string> input;
  std::ifstream file(absl::GetFlag(FLAGS_in_file));
  std::string line;
  while (std::getline(file, line)) {
    input.push_back(line);
  }

  return input;
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  absl::ParseCommandLine(argc, argv);

  absl::StatusOr<int64_t> result;
  auto input = ReadInput();
  auto first = !absl::GetFlag(FLAGS_second_part);
  if (first) {
    result = ValidPassports(input, false);
  } else {
    result = ValidPassports(input, true);
  }
  if (!result.ok()) {
    LOG(FATAL) << result.status().message();
  }
  std::cout << *result << std::endl;

  return EXIT_SUCCESS;
}
