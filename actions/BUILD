package(default_visibility = ["//visibility:public"])

cc_library(
    name = "action",
    hdrs = ["action.h"],
    deps = [
        "//actions/action:keystroke",
        "//actions/action:target",
        "@com_google_absl//absl/types:variant",
    ],
)

cc_library(
    name = "actions",
    hdrs = ["actions.h"],
    deps = [
        ":action",
        "//actions/internal:connection",
    ],
)
