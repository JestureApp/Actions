package(default_visibility = ["//visibility:public"])

cc_library(
    name = "keystroke",
    srcs = ["keystroke.cc"],
    hdrs = ["keystroke.h"],
    deps = [
        "@com_google_absl//absl/types:variant",
    ] + select({
        "@platforms//os:linux": ["//actions/internal/linux:keystroke"],
    }),
)

cc_library(
    name = "target",
    hdrs = ["target.h"],
    deps = [
        "@com_google_absl//absl/types:variant",
    ],
)