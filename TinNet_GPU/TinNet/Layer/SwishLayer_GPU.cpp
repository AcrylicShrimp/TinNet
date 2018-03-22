
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

	void SwishLayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::SwishLayer_GPU_forward(this->nFanIn, pInput, pOutput, this->nBeta);
	}

	void SwishLayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::SwishLayer_GPU_forwardBatch(nBatchSize, this->nFanIn, pInput, pOutput, this->nBeta);
	}

	void SwishLayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::SwishLayer_GPU_backwardBatch(nBatchSize, this->nFanIn, pForwardInput, pBackwardInput, pBackwardOutput, this->nBeta);
	}

	void SwishLayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}

	void SwishLayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}
}