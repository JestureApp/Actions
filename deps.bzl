"""Dependencies for actions package."""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

deps_remote_repositories = {
    "bazel_skylib": {
        "urls": [
            "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
            "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
        ],
        "sha256": "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
    },
    "com_google_absl": {
        "url": "https://github.com/abseil/abseil-cpp/archive/refs/tags/20220623.1.tar.gz",
        "strip_prefix": "abseil-cpp-20220623.1",
        "sha256": "91ac87d30cc6d79f9ab974c51874a704de9c2647c40f6932597329a282217ba8",
    },
    "com_google_googletest": {
        "url": "https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz",
        "strip_prefix": "googletest-release-1.12.1",
    },
}

def actions_repositiories():
    for name, args in deps_remote_repositories.items():
        maybe(
            http_archive,
            name = name,
            **args
        )

    maybe(
        native.new_local_repository,
        name = "xcb",
        path = "/usr",
        # CHECKME: Might need this path to be scoped differently for use outside of repository
        build_file = "@//third_party:xcb.BUILD",
    )

    maybe(
        native.new_local_repository,
        name = "X11",
        path = "/usr",
        # CHECKME: Might need this path to be scoped differently for use outside of repository
        build_file = "@//third_party:X11.BUILD",
    )
