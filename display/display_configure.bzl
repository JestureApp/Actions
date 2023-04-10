"""
Rules for detecting and setting up display server dependencies
"""

load("@bazel_skylib//lib:paths.bzl", "paths")

_x11_install_paths = {
    "default": {
        "path": "/usr",
        "include": "include/X11",
        "lib": "lib",
    },
    "xquartz": {
        "path": "/usr/X11",
        "include": "include",
        "lib": "lib",
    },
}

_xcb_install_paths = {
    "default": {
        "path": "/usr",
        "include": "include/xcb",
        "lib": "lib",
    },
    "xquartz": {
        "path": "/usr/xcb",
        "include": "include",
        "lib": "lib",
    },
}

def x11_install(
        name,
        path,
        include,
        lib):
    if name in _x11_install_paths:
        fail("x11 install with name %s already exists")

    _x11_install_paths[name] = {
        "path": path,
        "include": include,
        "lib": lib,
    }

def xcb_install(
        name,
        path,
        include,
        lib):
    if name in _xcb_install_paths:
        fail("xcb install with name %s already exists")

    _xcb_install_paths[name] = {
        "path": path,
        "include": include,
        "lib": lib,
    }

def _find_x11_install(repository_ctx):
    for name, install_paths in _x11_install_paths.items():
        base = install_paths["path"]

        inc_abs = paths.join(base, install_paths["include"])
        lib_abs = paths.join(base, install_paths["lib"])

        # print(inc_abs)

        if repository_ctx.path(inc_abs).exists and \
           repository_ctx.path(lib_abs).exists:
            return True, install_paths

    return False, _x11_install_paths["default"]

def _find_xcb_install(repository_ctx):
    for name, install_paths in _xcb_install_paths.items():
        base = install_paths["path"]

        inc_abs = paths.join(base, install_paths["include"])
        lib_abs = paths.join(base, install_paths["lib"])

        # print(inc_abs)

        if repository_ctx.path(inc_abs).exists and \
           repository_ctx.path(lib_abs).exists:
            return True, install_paths

    return False, _xcb_install_paths["default"]

def _display_autoconf_impl(repository_ctx):
    display_type = "unknown"

    has_x11, local_x11 = _find_x11_install(repository_ctx)
    has_xcb, local_xcb = _find_xcb_install(repository_ctx)

    if has_x11 and has_xcb:
        display_type = "x11"
    else:
        print("Failed to detect display server")  # buildifier: disable=print

    repository_ctx.file("BUILD", "# empty BUILD file so that bazel sees this as a valid package directory")
    repository_ctx.template(
        "BUILD",
        repository_ctx.path(Label("@actions//display:display.tpl.BUILD")),
        {
            "${default_display_type}": display_type,
        },
    )

    repository_ctx.template(
        "local_display.bzl",
        repository_ctx.path(Label("@actions//display:local_display.tpl.bzl")),
        {
            "${x11_path}": local_x11["path"],
            "${x11_include_path}": local_x11["include"],
            "${x11_lib_path}": local_x11["lib"],
            "${xcb_path}": local_xcb["path"],
            "${xcb_include_path}": local_xcb["include"],
            "${xcb_lib_path}": local_xcb["lib"],
            "${default_display_type}": display_type,
        },
    )

display_autoconf = repository_rule(
    implementation = _display_autoconf_impl,
    configure = True,
)

def display_configure():
    display_autoconf(name = "display")
