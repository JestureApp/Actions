package(default_visibility = ["//visibility:public"])

cc_library(
    name = "keystroke",
    srcs = ["keystroke.cc"],
    hdrs = ["keystroke.h"],
)

cc_test(
    name = "keystroke_test",
    size = "small",
    srcs = ["keystroke_test.cc"],
    tags = ["unit"],
    deps = [
        ":keystroke",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "target",
    hdrs = ["target.h"],
    deps = [
        "@com_google_absl//absl/types:variant",
    ],
)
