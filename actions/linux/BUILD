package(default_visibility = ["//visibility:public"])

cc_library(
    name = "dispatcher",
    srcs = ["dispatcher.cc"],
    hdrs = ["dispatcher.h"],
    deps = [
        "//actions:dispatcher_base",
        "//actions:keystroke",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_test(
    name = "dispatcher_test",
    size = "small",
    srcs = ["dispatcher_test.cc"],
    tags = ["unit"],
    deps = [
        ":dispatcher",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_googletest//:gtest_main",
    ],
)
