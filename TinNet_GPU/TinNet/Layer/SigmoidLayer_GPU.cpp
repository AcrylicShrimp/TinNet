
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

	void SigmoidLayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::SigmoidLayer_GPU_forward(this->nFanIn, pInput, pOutput);
	}

	void SigmoidLayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::SigmoidLayer_GPU_forwardBatch(nBatchSize, this->nFanIn, pInput, pOutput);
	}

	void SigmoidLayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::SigmoidLayer_GPU_backwardBatch(nBatchSize, this->nFanIn, pForwardInput, pBackwardInput, pBackwardOutput);
	}

	void SigmoidLayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}

	void SigmoidLayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}
}