
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_TINNET_GPU_BACKEND_H

#define _CLASS_TINNET_TINNET_GPU_BACKEND_H

#include "../../TinNet/TinNet/TinNetDLL.h"

#include "GPUVector.h"

#include <cstddef>

TINNET_DLL void mergeBatch(std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void updateParam(std::size_t nBiasSize, std::size_t nWeightSize, TinNet::GPUVector &sBias, TinNet::GPUVector &sWeight, const TinNet::GPUVector &sBiasDelta, const TinNet::GPUVector &sWeightDelta);
TINNET_DLL void updateParamFactor(std::size_t nBiasSize, std::size_t nWeightSize, TinNet::GPUVector &sBias, TinNet::GPUVector &sWeight, const TinNet::GPUVector &sBiasDelta, const TinNet::GPUVector &sWeightDelta, float nFactor);

#pragma region Loss_GPU

TINNET_DLL void MSE_GPU_derivative(std::size_t nIndex, std::size_t nBatchSize, std::size_t nOutputSize, const TinNet::GPUVector &sOutput, const TinNet::GPUVector &sDesiredOutput, TinNet::GPUVector &sResult);
TINNET_DLL void CE_GPU_derivative(std::size_t nIndex, std::size_t nBatchSize, std::size_t nOutputSize, const TinNet::GPUVector &sOutput, const TinNet::GPUVector &sDesiredOutput, TinNet::GPUVector &sResult);
TINNET_DLL void MulticlassCE_GPU_derivative(std::size_t nIndex, std::size_t nBatchSize, std::size_t nOutputSize, const TinNet::GPUVector &sOutput, const TinNet::GPUVector &sDesiredOutput, TinNet::GPUVector &sResult);

#pragma endregion

#pragma region Layer_GPU

TINNET_DLL void ConvLayer_GPU_forward(
	std::size_t nWidth,
	std::size_t nHeight,
	std::size_t nChannel,
	std::size_t nFilter,
	std::size_t nFilterWidth,
	std::size_t nFilterHeight,
	std::size_t nStrideHorizontal,
	std::size_t nStrideVertical,
	std::size_t nOutputWidth,
	std::size_t nOutputHeight,
	std::size_t nZeroPaddingHorizontalNegative,
	std::size_t nZeroPaddingVerticalNegative,
	const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, const TinNet::GPUVector &sBias, const TinNet::GPUVector &sWeight);
TINNET_DLL void ConvLayer_GPU_forwardBatch(
	std::size_t nIndex,
	std::size_t nBatchSize,
	std::size_t nWidth,
	std::size_t nHeight,
	std::size_t nChannel,
	std::size_t nFilter,
	std::size_t nFilterWidth,
	std::size_t nFilterHeight,
	std::size_t nStrideHorizontal,
	std::size_t nStrideVertical,
	std::size_t nOutputWidth,
	std::size_t nOutputHeight,
	std::size_t nZeroPaddingHorizontalNegative,
	std::size_t nZeroPaddingVerticalNegative,
	const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, const TinNet::GPUVector &sBias, const TinNet::GPUVector &sWeight);
TINNET_DLL void ConvLayer_GPU_backwardBatch(
	std::size_t nIndex,
	std::size_t nBatchSize,
	std::size_t nWidth,
	std::size_t nHeight,
	std::size_t nChannel,
	std::size_t nFilter,
	std::size_t nFilterWidth,
	std::size_t nFilterHeight,
	std::size_t nStrideHorizontal,
	std::size_t nStrideVertical,
	std::size_t nOutputWidth,
	std::size_t nOutputHeight,
	std::size_t nZeroPaddingHorizontalNegative,
	std::size_t nZeroPaddingVerticalNegative,
	const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput, TinNet::GPUVector &sBiasDelta, TinNet::GPUVector &sWeightDelta, const TinNet::GPUVector &sWeight);

TINNET_DLL void FullLayer_GPU_forward(std::size_t nInputSize, std::size_t nOutputSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, const TinNet::GPUVector &sBias, const TinNet::GPUVector &sWeight);
TINNET_DLL void FullLayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nInputSize, std::size_t nOutputSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, const TinNet::GPUVector &sBias, const TinNet::GPUVector &sWeight);
TINNET_DLL void FullLayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nInputSize, std::size_t nOutputSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput, TinNet::GPUVector &sBiasDelta, TinNet::GPUVector &sWeightDelta, const TinNet::GPUVector &sWeight);

TINNET_DLL void LReLULayer_GPU_forward(std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void LReLULayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void LReLULayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput);

TINNET_DLL void PReLULayer_GPU_forward(std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, float nParam);
TINNET_DLL void PReLULayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, float nParam);
TINNET_DLL void PReLULayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput, float nParam);

TINNET_DLL void ReLULayer_GPU_forward(std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void ReLULayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void ReLULayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput);

TINNET_DLL void SigmoidLayer_GPU_forward(std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void SigmoidLayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void SigmoidLayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput);

TINNET_DLL void SwishLayer_GPU_forward(std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, float nBeta);
TINNET_DLL void SwishLayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput, float nBeta);
TINNET_DLL void SwishLayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput, float nBeta);

TINNET_DLL void SoftmaxLayer_GPU_forward(std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void SoftmaxLayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void SoftmaxLayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput);

TINNET_DLL void TanhLayer_GPU_forward(std::size_t nSize, const  TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void TanhLayer_GPU_forwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sInput, TinNet::GPUVector &sOutput);
TINNET_DLL void TanhLayer_GPU_backwardBatch(std::size_t nIndex, std::size_t nBatchSize, std::size_t nSize, const TinNet::GPUVector &sForwardInput, const TinNet::GPUVector &sBackwardInput, TinNet::GPUVector &sBackwardOutput);

#pragma endregion

#endif