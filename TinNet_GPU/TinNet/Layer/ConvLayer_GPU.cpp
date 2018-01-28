
/*
	2018.01.24
	Created by AcrylicShrimp.
*/

#include "ConvLayer_GPU.h"

namespace TinNet::Layer
{
	ConvLayer_GPU::ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
								 std::size_t nNewFilterWidth,
								 std::size_t nNewFilterHeight) :
		ConvLayer_GPU(nNewWidth, nNewHeight, nNewChannel, nNewFilter,
				  nNewFilterWidth,
				  nNewFilterHeight,
				  1u,
				  1u)
	{
		//Empty.
	}

	ConvLayer_GPU::ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
								 std::size_t nNewFilterWidth,
								 std::size_t nNewFilterHeight,
								 std::size_t nNewStrideHorizontal,
								 std::size_t nNewStrideVertical) :
		ConvLayer_GPU(nNewWidth, nNewHeight, nNewChannel, nNewFilter,
				  nNewFilterWidth,
				  nNewFilterHeight,
				  nNewStrideHorizontal,
				  nNewStrideVertical,
				  nNewWidth,
				  nNewHeight)
	{
		//Empty.
	}

	ConvLayer_GPU::ConvLayer_GPU(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
								 std::size_t nNewFilterWidth,
								 std::size_t nNewFilterHeight,
								 std::size_t nNewStrideHorizontal,
								 std::size_t nNewStrideVertical,
								 std::size_t nNewOutputWidth,
								 std::size_t nNewOutputHeight) :
		Layer_GPU(nNewWidth * nNewHeight * nNewChannel, nNewOutputWidth * nNewOutputHeight * nNewFilter),
		nWidth{nNewWidth},
		nHeight{nNewHeight},
		nChannel{nNewChannel},
		nFilter{nNewFilter},
		nFilterWidth{nNewFilterWidth},
		nFilterHeight{nNewFilterHeight},
		nStrideHorizontal{nNewStrideHorizontal},
		nStrideVertical{nNewStrideVertical},
		nOutputWidth{nNewOutputWidth},
		nOutputHeight{nNewOutputHeight}
	{
		if ((this->nZeroPaddingHorizontalNegative = this->nZeroPaddingHorizontalPositive = ((this->nOutputWidth - 1u) * this->nStrideHorizontal + this->nFilterWidth - this->nWidth) / 2u) & 1u)
			++this->nZeroPaddingHorizontalPositive;

		if ((this->nZeroPaddingVerticalNegative = this->nZeroPaddingVerticalPositive = ((this->nOutputHeight - 1u) * this->nStrideVertical + this->nFilterHeight - this->nHeight) / 2u) & 1u)
			++this->nZeroPaddingVerticalPositive;

		cuMemAlloc(&this->pBias, sizeof(float) * nNewFilter);
		cuMemAlloc(&this->pWeight, sizeof(float) * nNewFilter * nNewChannel * nNewFilterWidth * nNewFilterHeight);
	}

	ConvLayer_GPU::~ConvLayer_GPU()
	{
		cuMemFree(this->pBias);
		cuMemFree(this->pWeight);

		this->pBias = 0;
		this->pWeight = 0;
	}

	const char *ConvLayer_GPU::name() const
	{
		return "ConvLayer_GPU";
	}

	void ConvLayer_GPU::initBias(std::function<float()> sGenerator)
	{
		std::vector<float> sBias(this->nFanOut);

		for (auto &nBias : sBias)
			nBias = sGenerator();

		cuMemcpyHtoD(this->pBias, sBias.data(), sizeof(float) * this->nFilter);
	}

	void ConvLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		std::vector<float> sWeight(this->nFanIn * this->nFanOut);

		for (auto &nWeight : sWeight)
			nWeight = sGenerator();

		cuMemcpyHtoD(this->pWeight, sWeight.data(), sizeof(float) * this->nFilter * this->nChannel * this->nFilterWidth * this->nFilterHeight);
	}

	void ConvLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nWeightDeltaSize = (nBiasDeltaSize = this->nFilter) * this->nChannel * this->nFilterWidth * this->nFilterHeight;
	}

	void ConvLayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::ConvLayer_GPU_forward(
			this->nWidth,
			this->nHeight,
			this->nChannel,
			this->nFilter,
			this->nFilterWidth,
			this->nFilterHeight,
			this->nStrideHorizontal,
			this->nStrideVertical,
			this->nOutputWidth,
			this->nOutputHeight,
			this->nZeroPaddingHorizontalNegative,
			this->nZeroPaddingVerticalNegative,
			pInput, pOutput, this->pBias, this->pWeight);
	}

	void ConvLayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::ConvLayer_GPU_forwardBatch(
			nBatchSize,
			this->nWidth,
			this->nHeight,
			this->nChannel,
			this->nFilter,
			this->nFilterWidth,
			this->nFilterHeight,
			this->nStrideHorizontal,
			this->nStrideVertical,
			this->nOutputWidth,
			this->nOutputHeight,
			this->nZeroPaddingHorizontalNegative,
			this->nZeroPaddingVerticalNegative,
			pInput, pOutput, this->pBias, this->pWeight);
	}

	void ConvLayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::ConvLayer_GPU_backwardBatch(
			nBatchSize,
			this->nWidth,
			this->nHeight,
			this->nChannel,
			this->nFilter,
			this->nFilterWidth,
			this->nFilterHeight,
			this->nStrideHorizontal,
			this->nStrideVertical,
			this->nOutputWidth,
			this->nOutputHeight,
			this->nZeroPaddingHorizontalNegative,
			this->nZeroPaddingVerticalNegative,
			pForwardInput, pBackwardInput, pBackwardOutput, pBiasDelta, pWeightDelta, this->pWeight);
	}

	void ConvLayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		::updateParam(this->nFilter, this->nFilter * this->nChannel * this->nFilterWidth * this->nFilterHeight, this->pBias, this->pWeight, pBiasDelta, pWeightDelta);
	}

	void ConvLayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		::updateParamFactor(this->nFilter, this->nFilter * this->nChannel * this->nFilterWidth * this->nFilterHeight, this->pBias, this->pWeight, pBiasDelta, pWeightDelta, nFactor);
	}
}