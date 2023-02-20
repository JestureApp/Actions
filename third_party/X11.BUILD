cc_library(
    name = "X11",
    # buildifier: disable=constant-globs
    hdrs = glob([
        "include/X11/**/*.h*",
    ]),
    includes = [
        "include/X11/",
    ],
    linkopts = [
        "-l:libX11.so",
    ],
    target_compatible_with = ["@platforms//os:linux"],
    visibility = ["//visibility:public"],
)
