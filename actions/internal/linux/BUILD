package(default_visibility = ["//actions:__subpackages__"])

cc_library(
    name = "keystroke",
    srcs = ["keystroke.cc"],
    hdrs = ["keystroke.h"],
    deps = [
        "@X11",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@xcb",
    ],
    alwayslink = 1,
)

cc_library(
    name = "xcb_connection",
    srcs = ["xcb_connection.cc"],
    hdrs = ["xcb_connection.h"],
    deps = [
        ":xcb_error",
        ":xcb_keyboard",
        "//actions/internal:connection",
        "//actions/internal:util",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/types:variant",
        "@xcb",
    ],
)

cc_library(
    name = "xcb_error",
    srcs = ["xcb_error.cc"],
    hdrs = ["xcb_error.h"],
    deps = [
        "@com_google_absl//absl/status:status",
        "@xcb",
    ],
)

cc_library(
    name = "xcb_keyboard",
    srcs = ["xcb_keyboard.cc"],
    hdrs = ["xcb_keyboard.h"],
    deps = [
        ":xcb_error",
        "//actions/action:keystroke",
        "//actions/internal:util",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@xcb",
    ],
)
