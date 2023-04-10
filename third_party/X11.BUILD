load("@bazel_skylib//lib:paths.bzl", "paths")
load("@display//:local_display.bzl", "local_x11_include_path", "local_x11_lib_path", "local_x11_path")

cc_library(
    name = "X11",
    # buildifier: disable=constant-globs
    hdrs = glob([
        ("%s/**/*.h" % local_x11_include_path()),
    ]),
    includes = [
        local_x11_include_path(),
    ],
    linkopts = select({
        "@platforms//os:linux": ["-lX11"],
        # TODO: Check that this works on osx
        "@platforms//os:osx": [
            ("-F%s" % paths.join(
                local_x11_path(),
                local_x11_lib_path(),
            )),
            "-framework X11",
        ],
    }),
    target_compatible_with = ["@display//:x11"],
    visibility = ["//visibility:public"],
)
