
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

	void LReLULayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::LReLULayer_GPU_forward(this->nFanIn, pInput, pOutput);
	}

	void LReLULayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::LReLULayer_GPU_forwardBatch(nBatchSize, this->nFanIn, pInput, pOutput);
	}

	void LReLULayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::LReLULayer_GPU_backwardBatch(nBatchSize, this->nFanIn, pForwardInput, pBackwardInput, pBackwardOutput);
	}

	void LReLULayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}

	void LReLULayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}
}