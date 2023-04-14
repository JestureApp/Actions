load("@bazel_skylib//lib:paths.bzl", "paths")
load("@display//:local_display.bzl", "local_xcb_include_path", "local_xcb_lib_path", "local_xcb_path")

cc_library(
    name = "xcb",
    # buildifier: disable=constant-globs
    hdrs = glob([
        ("%s/**/*.h" % local_xcb_include_path()),
    ]),
    includes = [
        local_xcb_include_path(),
    ],
    linkopts = select({
        "@platforms//os:linux": [
            "-lxcb",
            "-lxcb-keysyms",
            "-lxcb-util",
            "-lxcb-xtest",
        ],
        # TODO: Check that this works on osx
        "@platforms//os:osx": [
            ("-F%s" % paths.join(
                local_xcb_path(),
                local_xcb_lib_path(),
            )),
            "-framework xcb",
            "-framework xcb-keysyms",
            "-framework xcb-util",
            "-framework xcb-xtest",
        ],
    }),
    target_compatible_with = ["@display//:x11"],
    visibility = ["//visibility:public"],
)
