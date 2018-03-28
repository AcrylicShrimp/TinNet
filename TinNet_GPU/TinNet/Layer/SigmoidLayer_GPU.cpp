
/*
	2018.01.21
	Created by AcrylicShrimp.
*/

#include "SigmoidLayer_GPU.h"

namespace TinNet::Layer
{
	SigmoidLayer_GPU::SigmoidLayer_GPU(std::size_t nFanIn) :
		Layer_GPU(nFanIn, nFanIn)
	{
		//Empty.
	}

	const char *SigmoidLayer_GPU::name() const
	{
		return "SigmoidLayer_GPU";
	}

	void SigmoidLayer_GPU::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SigmoidLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SigmoidLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void SigmoidLayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::SigmoidLayer_GPU_forward(this->nFanIn, sInput, sOutput);
	}

	void SigmoidLayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::SigmoidLayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, sInput, sOutput);
	}

	void SigmoidLayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::SigmoidLayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, sForwardInput, sBackwardInput, sBackwardOutput);
	}

	void SigmoidLayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}

	void SigmoidLayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}
}