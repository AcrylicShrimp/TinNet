
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

	void TanhLayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::TanhLayer_GPU_forward(this->nFanIn, pInput, pOutput);
	}

	void TanhLayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::TanhLayer_GPU_forwardBatch(nBatchSize, this->nFanIn, pInput, pOutput);
	}

	void TanhLayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::TanhLayer_GPU_backwardBatch(nBatchSize, this->nFanIn, pForwardInput, pBackwardInput, pBackwardOutput);
	}

	void TanhLayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}

	void TanhLayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		//Empty.
	}
}