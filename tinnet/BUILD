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
        "src/node/StandardNode.cpp",
    ],
    hdrs = [
        "includes/compute/Denormal.h",
        "includes/compute/GEMM.h",
        "includes/memory/ScopedStorage.h",
        "includes/node/Builder.h",
        "includes/node/Node.h",
        "includes/node/Shape.h",
        "includes/node/StandardNode.h",
        "includes/node/Type.h",
        "includes/platform/CallingConvention.h",
        "includes/platform/Platform.h",
    ],
    copts = [
        "-std=c++17",
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
        "tests/memory/scopedstorage.cpp",
        "tests/node/shape.cpp",
    ],
    copts = [
        "-std=c++17",
        "-O3 -mllvm -polly",
    ],
    deps = [
        "//tinnet:main",
        "@catch2//:main",
    ],
)
