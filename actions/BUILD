package(default_visibility = ["//visibility:public"])

cc_library(
    name = "action",
    hdrs = ["action.h"],
    deps = [
        "//actions/action:cursor_move",
        "//actions/action:keystroke",
        "//actions/action:target",
        "@com_google_absl//absl/types:variant",
    ],
)

cc_library(
    name = "actions",
    srcs = ["actions.cc"],
    hdrs = ["actions.h"],
    copts = select({
        "@display//:x11": ["-D __x11__"],
        "//conditions:default": [],
    }),
    deps = [
        ":action",
        "//actions/internal:connection",
        "//actions/internal:util",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ] + select({
        "@display//:x11": ["//actions/internal/x11:xcb_connection"],
        "//conditions:default": ["//actions/internal/stub:stub_connection"],
    }),
)

cc_test(
    name = "actions_test",
    size = "small",
    srcs = ["actions_test.cc"],
    tags = ["unit"],
    deps = [
        ":actions",
        "//actions/internal:connection",
        "//actions/internal:util",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_googletest//:gtest_main",
    ],
)
