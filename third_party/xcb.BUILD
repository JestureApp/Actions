cc_library(
    name = "xcb",
    # buildifier: disable=constant-globs
    hdrs = glob([
        "include/xcb/**/*.h*",
    ]),
    includes = [
        "include/xcb/",
    ],
    linkopts = [
        "-l:libxcb-keysyms.so",
        "-l:libxcb-util.so",
        "-l:libxcb-xtest.so",
        "-l:libxcb.so",
    ],
    target_compatible_with = ["@platforms//os:linux"],
    visibility = ["//visibility:public"],
)
