package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "actions_keystroke",
    srcs = ["actions_keystroke.cc"],
    deps = [
        "//actions",
        "//actions:action",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/status",
    ],
)

cc_binary(
    name = "actions_mouse",
    srcs = ["actions_mouse.cc"],
    deps = [
        "//actions",
        "//actions:action",
        "@com_google_absl//absl/status",
    ],
)
