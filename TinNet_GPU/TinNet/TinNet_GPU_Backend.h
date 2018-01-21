
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_TINNET_GPU_BACKEND_H

#define _CLASS_TINNET_TINNET_GPU_BACKEND_H

#include "../../TinNet/TinNet/TinNetDLL.h"

#include "cuda.h"

#include <cstddef>

TINNET_DLL void mergeBatch(std::size_t nBatchSize, std::size_t nSize, CUdeviceptr pInput, CUdeviceptr pOutput);

#pragma region Loss_GPU

#pragma region MSE_GPU

TINNET_DLL void MSE_GPU_derivative(std::size_t nBatchSize, std::size_t nOutputSize, CUdeviceptr pOutput, CUdeviceptr pDesiredOutput, CUdeviceptr pResult);

#pragma endregion

#pragma endregion

#pragma region Layer_GPU

TINNET_DLL void FullLayer_GPU_forward(std::size_t nInputSize, std::size_t nOutputSize, CUdeviceptr pInput, CUdeviceptr pOutput, CUdeviceptr pBias, CUdeviceptr pWeight);
TINNET_DLL void FullLayer_GPU_forwardBatch(std::size_t nBatchSize, std::size_t nInputSize, std::size_t nOutputSize, CUdeviceptr pInput, CUdeviceptr pOutput, CUdeviceptr pBias, CUdeviceptr pWeight);
TINNET_DLL void FullLayer_GPU_backwardBatch(std::size_t nBatchSize, std::size_t nInputSize, std::size_t nOutputSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta, CUdeviceptr pWeight);
TINNET_DLL void FullLayer_GPU_updateParam(std::size_t nBiasSize, std::size_t nWeightSize, CUdeviceptr pBias, CUdeviceptr pWeight, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta);
TINNET_DLL void FullLayer_GPU_updateParamFactor(std::size_t nBiasSize, std::size_t nWeightSize, CUdeviceptr pBias, CUdeviceptr pWeight, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta, float nFactor);

TINNET_DLL void SigmoidLayer_GPU_forward(std::size_t nSize, CUdeviceptr pInput, CUdeviceptr pOutput);
TINNET_DLL void SigmoidLayer_GPU_forwardBatch(std::size_t nBatchSize, std::size_t nSize, CUdeviceptr pInput, CUdeviceptr pOutput);
TINNET_DLL void SigmoidLayer_GPU_backwardBatch(std::size_t nBatchSize, std::size_t nSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput);

TINNET_DLL void TanhLayer_GPU_forward(std::size_t nSize, CUdeviceptr pInput, CUdeviceptr pOutput);
TINNET_DLL void TanhLayer_GPU_forwardBatch(std::size_t nBatchSize, std::size_t nSize, CUdeviceptr pInput, CUdeviceptr pOutput);
TINNET_DLL void TanhLayer_GPU_backwardBatch(std::size_t nBatchSize, std::size_t nSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput);

#pragma endregion

#endif