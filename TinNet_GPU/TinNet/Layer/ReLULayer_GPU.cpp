
/*
	2018.01.22
	Created by AcrylicShrimp.
*/

#include "ReLULayer_GPU.h"

namespace TinNet::Layer
{
	ReLULayer_GPU::ReLULayer_GPU(std::size_t nFanIn) :
		Layer_GPU(nFanIn, nFanIn)
	{
		//Empty.
	}

	const char *ReLULayer_GPU::name() const
	{
		return "ReLULayer_GPU";
	}

	void ReLULayer_GPU::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void ReLULayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void ReLULayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void ReLULayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::ReLULayer_GPU_forward(this->nFanIn, sInput, sOutput);
	}

	void ReLULayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::ReLULayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, sInput, sOutput);
	}

	void ReLULayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::ReLULayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, sForwardInput, sBackwardInput, sBackwardOutput);
	}

	void ReLULayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}

	void ReLULayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}
}