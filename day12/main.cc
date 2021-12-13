#include <glog/logging.h>
#include <sys/resource.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/status/statusor.h"
#include "day12/solution.h"

ABSL_FLAG(std::string, in_file, "", "file with input data");
ABSL_FLAG(bool, second_part, false, "whether to run the 2nd part");

std::vector<std::string> ReadInput() {
  std::ifstream myfile(absl::GetFlag(FLAGS_in_file));
  LOG(INFO) << absl::GetFlag(FLAGS_in_file);
  LOG(INFO) << strerror(errno);
  std::vector<std::string> input;
  std::string line;
  while (std::getline(myfile, line)) {
    input.push_back(line);
  }
  return input;
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  absl::ParseCommandLine(argc, argv);

  const rlim_t kStackSize = 100 * 1024 * 1024;
  struct rlimit rl;
  int r;

  r = getrlimit(RLIMIT_STACK, &rl);
  if (r == 0) {
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      r = setrlimit(RLIMIT_STACK, &rl);
      if (r != 0) {
        fprintf(stderr, "setrlimit returned result = %d\n", r);
      }
    }
  }

  absl::StatusOr<int64_t> result;
  auto input = ReadInput();
  auto first = !absl::GetFlag(FLAGS_second_part);
  if (first) {
    result = Caves(input);
  } else {
    result = CavesRepetition(input);
  }
  if (!result.ok()) {
    LOG(FATAL) << result.status().message();
  }
  std::cout << *result << std::endl;

  return EXIT_SUCCESS;
}
