cc_library(
  name = "solution",
  deps = [
    "@com_google_absl//absl/container:flat_hash_set",
    "@com_github_google_glog//:glog",
    "@com_google_absl//absl/status:statusor",
  ],
  srcs = ["solution.cc"],
  hdrs = ["solution.h"],
)

cc_test(
    name = "test",
    srcs = ["test.cc"],
    deps = [
        ":solution",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
  name = "main",
  deps = [
    ":solution",
    "@com_google_absl//absl/flags:flag",
    "@com_google_absl//absl/flags:parse",
  ],
  srcs = ["main.cc"],
)
