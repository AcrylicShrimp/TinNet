
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#include "SoftmaxLayer_GPU.h"

namespace TinNet::Layer
{
	SoftmaxLayer_GPU::SoftmaxLayer_GPU(std::size_t nFanIn) :
		Layer_GPU(nFanIn, nFanIn)
	{
		//Empty.
	}
	
	const char *SoftmaxLayer_GPU::name() const
	{
		return "SoftmaxLayer_GPU";
	}

	void SoftmaxLayer_GPU::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SoftmaxLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SoftmaxLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void SoftmaxLayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::SoftmaxLayer_GPU_forward(this->nFanIn, sInput, sOutput);
	}

	void SoftmaxLayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::SoftmaxLayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, sInput, sOutput);
	}

	void SoftmaxLayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::SoftmaxLayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, sForwardInput, sBackwardInput, sBackwardOutput);
	}

	void SoftmaxLayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}

	void SoftmaxLayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}
}