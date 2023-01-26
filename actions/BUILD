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
    name = "connection",
    hdrs = ["connection.h"],
    deps = [
        ":keystroke",
        ":promise",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "dispatcher",
    hdrs = ["dispatcher.h"],
    deps = [],
)

cc_library(
    name = "keystroke",
    hdrs = ["keystroke.h"],
)

cc_library(
    name = "promise",
    hdrs = ["promise.h"],
)
