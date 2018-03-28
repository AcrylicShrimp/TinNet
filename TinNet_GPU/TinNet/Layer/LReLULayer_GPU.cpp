
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#include "LReLULayer_GPU.h"

namespace TinNet::Layer
{
	LReLULayer_GPU::LReLULayer_GPU(std::size_t nFanIn) :
		Layer_GPU(nFanIn, nFanIn)
	{
		//Empty.
	}

	const char *LReLULayer_GPU::name() const
	{
		return "LReLULayer_GPU";
	}

	void LReLULayer_GPU::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void LReLULayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void LReLULayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void LReLULayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::LReLULayer_GPU_forward(this->nFanIn, sInput, sOutput);
	}

	void LReLULayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::LReLULayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, sInput, sOutput);
	}

	void LReLULayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::LReLULayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, sForwardInput, sBackwardInput, sBackwardOutput);
	}

	void LReLULayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}

	void LReLULayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}
}