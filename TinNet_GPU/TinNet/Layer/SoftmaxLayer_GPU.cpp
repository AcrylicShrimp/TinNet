
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

	void SoftmaxLayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::SoftmaxLayer_GPU_forward(this->nFanIn, pInput, pOutput);
	}

	void SoftmaxLayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::SoftmaxLayer_GPU_forwardBatch(nBatchSize, this->nFanIn, pInput, pOutput);
	}

	void SoftmaxLayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::SoftmaxLayer_GPU_backwardBatch(nBatchSize, this->nFanIn, pForwardInput, pBackwardInput, pBackwardOutput);
	}

	void SoftmaxLayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}

	void SoftmaxLayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}
}