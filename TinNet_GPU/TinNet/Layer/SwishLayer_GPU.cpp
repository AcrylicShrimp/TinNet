
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "SwishLayer_GPU.h"

namespace TinNet::Layer
{
	SwishLayer_GPU::SwishLayer_GPU(std::size_t nFanIn, float nBeta) :
		Layer_GPU(nFanIn, nFanIn),
		nBeta{nBeta}
	{
		//Empty.
	}
	
	const char *SwishLayer_GPU::name() const
	{
		return "SwishLayer_GPU";
	}

	void SwishLayer_GPU::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SwishLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SwishLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void SwishLayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::SwishLayer_GPU_forward(this->nFanIn, sInput, sOutput, this->nBeta);
	}

	void SwishLayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::SwishLayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, sInput, sOutput, this->nBeta);
	}

	void SwishLayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::SwishLayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, sForwardInput, sBackwardInput, sBackwardOutput, this->nBeta);
	}

	void SwishLayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}

	void SwishLayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}
}