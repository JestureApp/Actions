package(default_visibility = ["//actions:__subpackages__"])

cc_library(
    name = "connection",
    hdrs = ["connection.h"],
    deps = [
        "//actions:action",
        "@com_google_absl//absl/status",
    ],
)

cc_library(
    name = "util",
    hdrs = ["util.h"],
    deps = ["@com_google_absl//absl/status"],
)

cc_test(
    name = "util_test",
    size = "small",
    srcs = ["util_test.cc"],
    tags = ["unit"],
    deps = [
        ":util",
        "@com_google_googletest//:gtest_main",
    ],
)
