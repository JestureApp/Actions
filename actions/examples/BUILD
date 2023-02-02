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
    name = "keysym_experiment",
    srcs = ["keysym_experiment.cc"],
    deps = [
        "@xcb",
    ],
)

cc_binary(
    name = "keysym_experiment_x11",
    srcs = ["keysym_experiment_x11.cc"],
    deps = [
        "@X11",
        "@xcb",
    ],
)
