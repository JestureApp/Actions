"""
Local Qt installation helper functions
"""

# load("@bazel_skylib//lib:paths.bzl", "paths")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def local_x11_path():
    return "${x11_path}"

def local_x11_include_path():
    return "${x11_include_path}"

def local_x11_lib_path():
    return "${x11_lib_path}"

def local_xcb_path():
    return "${xcb_path}"

def local_xcb_include_path():
    return "${xcb_include_path}"

def local_xcb_lib_path():
    return "${xcb_lib_path}"

def display_constraints(name):
    native.constraint_setting(
        name = "display_type",
        default_constraint_value = "${default_display_type}",
    )

    native.constraint_value(name = "unknown", constraint_setting = ":display_type")

    native.constraint_value(name = "x11", constraint_setting = ":display_type")

def display_repositories():
    maybe(
        native.new_local_repository,
        name = "X11",
        path = local_x11_path(),
        build_file = "@actions//third_party:X11.BUILD",
    )

    maybe(
        native.new_local_repository,
        name = "xcb",
        path = local_xcb_path(),
        build_file = "@actions//third_party:xcb.BUILD",
    )
