# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "tinnet",
    srcs = [
        "src/compute/Denormal.cpp",
        "src/compute/GEMM.cpp",
        "src/node/Shape.cpp",
    ],
    hdrs = [
        "includes/compute/Denormal.h",
        "includes/compute/GEMM.h",
        "includes/node/Shape.h",
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
