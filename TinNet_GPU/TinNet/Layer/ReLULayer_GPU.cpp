
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

	void ReLULayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::ReLULayer_GPU_forward(this->nFanIn, pInput, pOutput);
	}

	void ReLULayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::ReLULayer_GPU_forwardBatch(nBatchSize, this->nFanIn, pInput, pOutput);
	}

	void ReLULayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::ReLULayer_GPU_backwardBatch(nBatchSize, this->nFanIn, pForwardInput, pBackwardInput, pBackwardOutput);
	}

	void ReLULayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}

	void ReLULayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}
}