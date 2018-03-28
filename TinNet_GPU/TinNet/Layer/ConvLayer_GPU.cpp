
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
		sBias{0},
		sWeight{0},
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

		this->sBias.resize(nNewFilter);
		this->sWeight.resize(nNewFilter * nNewChannel * nNewFilterWidth * nNewFilterHeight);
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

		this->sBias = sBias;
	}

	void ConvLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		std::vector<float> sWeight(this->nFanIn * this->nFanOut);

		for (auto &nWeight : sWeight)
			nWeight = sGenerator();

		this->sWeight = sWeight;
	}

	void ConvLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nWeightDeltaSize = (nBiasDeltaSize = this->nFilter) * this->nChannel * this->nFilterWidth * this->nFilterHeight * this->nOutputWidth * this->nOutputHeight * 2;
	}

	void ConvLayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
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
			sInput, sOutput, this->sBias, this->sWeight);
	}

	void ConvLayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::ConvLayer_GPU_forwardBatch(
			nIndex,
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
			sInput, sOutput, this->sBias, this->sWeight);
	}

	void ConvLayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::ConvLayer_GPU_backwardBatch(
			nIndex,
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
			sForwardInput, sBackwardInput, sBackwardOutput, sBiasDelta, sWeightDelta, this->sWeight);
	}

	void ConvLayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		::updateParam(this->nFilter, this->nFilter * this->nChannel * this->nFilterWidth * this->nFilterHeight, this->sBias, this->sWeight, sBiasDelta, sWeightDelta);
	}

	void ConvLayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		::updateParamFactor(this->nFilter, this->nFilter * this->nChannel * this->nFilterWidth * this->nFilterHeight, this->sBias, this->sWeight, sBiasDelta, sWeightDelta, nFactor);
	}
}