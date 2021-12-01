#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/status/statusor.h"
#include "day01/solution.h"

ABSL_FLAG(std::string, in_file, "", "file with input data");
ABSL_FLAG(bool, second_part, false, "whether to run the 2nd part");

std::vector<int32_t> ReadInput() {
  std::fstream myfile(absl::GetFlag(FLAGS_in_file), std::ios_base::in);
  std::vector<int32_t> input;
  int32_t number;
  while (myfile >> number) {
    input.push_back(number);
  }
  return input;
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  absl::ParseCommandLine(argc, argv);

  absl::StatusOr<int32_t> result;
  auto numbers = ReadInput();
  auto first = !absl::GetFlag(FLAGS_second_part);
  if (first) {
    result = CountIncreases(numbers);
  } else {
    result = CountWindowIncreases(numbers);
  }
  if (!result.ok()) {
    LOG(FATAL) << result.status().message();
  }
  std::cout << *result << std::endl;

  return EXIT_SUCCESS;
}
