package(default_visibility = ["//visibility:public"])

cc_library(
    name = "connection",
    srcs = ["connection.cc"],
    hdrs = ["connection.h"],
    deps = [
        ":error",
        "//actions:connection_base",
        "//actions:keystroke",
        "@com_google_absl//absl/status:statusor",
        "@xcb",
        "@xcb//:keysyms",
        "@xcb//:xtest",
    ],
)

cc_library(
    name = "error",
    srcs = ["error.cc"],
    hdrs = ["error.h"],
    deps = [
        "@com_google_absl//absl/status",
        "@xcb",
    ],
)

cc_test(
    name = "connection_test",
    size = "small",
    srcs = ["connection_test.cc"],
    tags = ["unit"],
    deps = [
        ":connection",
        "@com_google_googletest//:gtest_main",
    ],
)
