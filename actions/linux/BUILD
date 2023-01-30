package(default_visibility = ["//visibility:public"])

cc_library(
    name = "xcb_error",
    srcs = ["xcb_error.cc"],
    hdrs = ["xcb_error.h"],
    deps = [
        "@com_google_absl//absl/status",
        "@xcb",
    ],
)

cc_library(
    name = "xcb_connection",
    srcs = ["xcb_connection.cc"],
    hdrs = ["xcb_connection.h"],
    deps = [
        ":xcb_error",
        ":xcb_promise",
        "//actions:connection",
        "//actions:keystroke",
        "//actions:promise",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@xcb",
    ],
)

cc_library(
    name = "xcb_promise",
    srcs = ["xcb_promise.cc"],
    hdrs = ["xcb_promise.h"],
    deps = [
        "//actions:promise",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@xcb",
    ],
)
