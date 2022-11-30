package(default_visibility = ["//visibility:public"])


cc_library(
    name = "keystroke",
    srcs = ["keystroke.cc"],
    hdrs = ["keystroke.h"],
    deps = [
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/status",
    ]
)

cc_library(
    name = "connection_base",
    hdrs = ["connection_base.h"],
    deps = [
        ":keystroke",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/status",
    ]
)

cc_library(
    name = "connection",
    srcs = ["connection.cc"],
    hdrs = ["connection.h"],
    deps = select({
        "@platforms//os:linux": ["//actions/linux:connection"],
    }) + [
        ":connection_base",
        "@com_google_absl//absl/status:statusor",
    ]
)

cc_library(
    name = "actions",
    hdrs = ["actions.h"],
    deps = [
        ":connection",
        ":keystroke",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/utility",
    ]
)