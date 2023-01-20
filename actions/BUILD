package(default_visibility = ["//visibility:public"])

cc_library(
    name = "actions",
    srcs = ["actions.cc"],
    hdrs = ["actions.h"],
    deps = [
        "dispatcher",
        ":keystroke",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "dispatcher",
    srcs = ["dispatcher.cc"],
    hdrs = ["dispatcher.h"],
    deps = [
        ":dispatcher_base",
    ] + select({
        "@platforms//os:linux": ["//actions/linux:dispatcher"],
    }),
)

cc_library(
    name = "dispatcher_base",
    hdrs = ["dispatcher_base.h"],
    deps = [
        ":keystroke",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "keystroke",
    hdrs = ["keystroke.h"],
)
