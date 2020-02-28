load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "main",
    srcs = [
        "src/compute/Denormal.cpp",
        "src/compute/GEMM.cpp",
        "src/memory/ScopedStorage.cpp",
        "src/node/Builder.cpp",
        "src/node/Node.cpp",
        "src/node/Shape.cpp",
        "src/node/kernel/BasicArithmetic.cpp",
        "src/node/kernel/MathFunction.cpp",
    ],
    hdrs = [
        "includes/compute/Denormal.h",
        "includes/compute/GEMM.h",
        "includes/memory/ScopedStorage.h",
        "includes/node/Builder.h",
        "includes/node/Node.h",
        "includes/node/Shape.h",
        "includes/node/Type.h",
        "includes/node/kernel/BasicArithmetic.h",
        "includes/node/kernel/MathFunction.h",
        "includes/platform/CallingConvention.h",
        "includes/platform/Platform.h",
    ],
    copts = [
        "-std=c++17",
        "-ffast-math",
        "-fopenmp",
        "-mavx2",
        "-mfma",
        "-O3 -mllvm -polly",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "test",
    timeout = "short",
    srcs = [
        "tests/helper/Random.h",
        "tests/memory/scopedstorage.cpp",
        "tests/node/kernel/add.cpp",
        "tests/node/kernel/div.cpp",
        "tests/node/kernel/log.cpp",
        "tests/node/kernel/mul.cpp",
        "tests/node/kernel/sub.cpp",
        "tests/node/shape.cpp",
    ],
    copts = [
        "-std=c++17",
        "-ffast-math",
        "-O3 -mllvm -polly",
    ],
    deps = [
        "//tinnet:main",
        "@catch2//:main",
    ],
)
