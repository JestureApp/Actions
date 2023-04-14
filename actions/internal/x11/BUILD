package(default_visibility = ["//actions:__subpackages__"])

cc_library(
    name = "keystroke",
    srcs = ["keystroke.cc"],
    hdrs = ["keystroke.h"],
    target_compatible_with = ["@display//:x11"],
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
    target_compatible_with = ["@display//:x11"],
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
    target_compatible_with = ["@display//:x11"],
    deps = [
        "@com_google_absl//absl/status",
        "@xcb",
    ],
)

cc_library(
    name = "xcb_keyboard",
    srcs = ["xcb_keyboard.cc"],
    hdrs = ["xcb_keyboard.h"],
    target_compatible_with = ["@display//:x11"],
    deps = [
        ":xcb_error",
        "//actions/action:keystroke",
        "//actions/internal:util",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@xcb",
    ],
)
