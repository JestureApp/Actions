
cc_binary(
    name = "xtest_demo",
    srcs = ["xtest_demo.cc"],
    deps = [
        "@xcb",
        "@xcb//:xtest",
        "@xcb//:keysyms",
        "@com_google_absl//absl/status"
    ]
)

cc_binary(
    name = "actions_demo",
    srcs = ["actions_demo.cc"],
    deps = [
        "//actions",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ]
)