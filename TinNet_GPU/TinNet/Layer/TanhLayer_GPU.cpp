
/*
	2018.01.21
	Created by AcrylicShrimp.
*/

#include "TanhLayer_GPU.h"

namespace TinNet::Layer
{
	TanhLayer_GPU::TanhLayer_GPU(std::size_t nFanIn) :
		Layer_GPU(nFanIn, nFanIn)
	{
		//Empty.
	}

	const char *TanhLayer_GPU::name() const
	{
		return "TanhLayer_GPU";
	}

	void TanhLayer_GPU::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void TanhLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void TanhLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void TanhLayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::TanhLayer_GPU_forward(this->nFanIn, sInput, sOutput);
	}

	void TanhLayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::TanhLayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, sInput, sOutput);
	}

	void TanhLayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::TanhLayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, sForwardInput, sBackwardInput, sBackwardOutput);
	}

	void TanhLayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}

	void TanhLayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		//Empty.
	}
}