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
    name = "actions_cursor",
    srcs = ["actions_cursor.cc"],
    deps = [
        "//actions",
        "//actions:action",
        "@com_google_absl//absl/status",
    ],
)
