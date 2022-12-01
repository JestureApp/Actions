package(default_visibility = ["//visibility:public"])

cc_library(
    name = "connection",
    srcs = ["connection.cc"],
    hdrs = ["connection.h"],
    deps = [
        ":error",
        "//actions:connection_base",
        "//actions:keystroke",
        "@xcb",
        "@xcb//:keysyms",
        "@xcb//:xtest",
        "@com_google_absl//absl/status:statusor",
    ]
)

cc_library(
    name = "error",
    srcs = ["error.cc"],
    hdrs = ["error.h"],
    deps = [
        "@xcb",
        "@com_google_absl//absl/status",
    ]
)

cc_test(
    name = "connection_test",
    srcs = ["connection_test.cc"],
    deps = [
        ":connection",
        "@com_google_googletest//:gtest_main",
    ]
)