load("@rules_cc//cc:defs.bzl", "cc_binary")

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "basic",
    srcs = ["src/main.cpp"],
    copts = [
        "-std=c++17",
        "-O3 -mllvm -polly",
    ],
    deps = ["//tinnet:main"],
)
