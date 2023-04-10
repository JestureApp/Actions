package(default_visibility = ["//visibility:public"])

cc_library(
    name = "keystroke",
    srcs = ["keystroke.cc"],
    hdrs = ["keystroke.h"],
    copts = select({
        "@display//:x11": ["-D __x11__"],
        "//conditions:default": [],
    }),
    deps = [
        "@com_google_absl//absl/types:variant",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ] + select({
        "@display//:x11": ["//actions/internal/x11:keystroke"],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "mouse",
    hdrs = ["mouse.h"],
)

cc_library(
    name = "target",
    hdrs = ["target.h"],
    deps = [
        "@com_google_absl//absl/types:variant",
    ],
)
