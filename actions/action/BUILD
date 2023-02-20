package(default_visibility = ["//visibility:public"])

cc_library(
    name = "keystroke",
    srcs = ["keystroke.cc"],
    hdrs = ["keystroke.h"],
    deps = [
        "@com_google_absl//absl/types:variant",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ] + select({
        "@platforms//os:linux": ["//actions/internal/linux:keystroke"],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "target",
    hdrs = ["target.h"],
    deps = [
        "@com_google_absl//absl/types:variant",
    ],
)
