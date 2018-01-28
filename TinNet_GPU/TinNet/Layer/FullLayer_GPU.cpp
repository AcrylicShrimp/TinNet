
/*
	2018.01.19
	Created by AcrylicShrimp.
*/

#include "FullLayer_GPU.h"

namespace TinNet::Layer
{
	FullLayer_GPU::FullLayer_GPU(std::size_t nFanIn, std::size_t nFanOut) :
		Layer_GPU(nFanIn, nFanOut)
	{
		cuMemAlloc(&this->pBias, sizeof(float) * nFanOut);
		cuMemAlloc(&this->pWeight, sizeof(float) * nFanIn * nFanOut);
	}

	FullLayer_GPU::~FullLayer_GPU()
	{
		cuMemFree(this->pBias);
		cuMemFree(this->pWeight);

		this->pBias = 0;
		this->pWeight = 0;
	}

	const char *FullLayer_GPU::name() const
	{
		return "FullLayer_GPU";
	}

	void FullLayer_GPU::initBias(std::function<float()> sGenerator)
	{
		std::vector<float> sBias(this->nFanOut);

		for (auto &nBias : sBias)
			nBias = sGenerator();

		cuMemcpyHtoD(this->pBias, sBias.data(), sizeof(float) * this->nFanOut);
	}

	void FullLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		std::vector<float> sWeight(this->nFanIn * this->nFanOut);

		for (auto &nWeight : sWeight)
			nWeight = sGenerator();

		cuMemcpyHtoD(this->pWeight, sWeight.data(), sizeof(float) * this->nFanIn * this->nFanOut);
	}

	void FullLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nWeightDeltaSize = this->nFanIn * (nBiasDeltaSize = this->nFanOut);
	}

	void FullLayer_GPU::forward(CUdeviceptr pInput, CUdeviceptr pOutput) const
	{
		::FullLayer_GPU_forward(this->nFanIn, this->nFanOut, pInput, pOutput, this->pBias, this->pWeight);
	}

	void FullLayer_GPU::forward(std::size_t nBatchSize, CUdeviceptr pInput, CUdeviceptr pOutput, bool bTrainingPhase) const
	{
		::FullLayer_GPU_forwardBatch(nBatchSize, this->nFanIn, this->nFanOut, pInput, pOutput, this->pBias, this->pWeight);
	}

	void FullLayer_GPU::backward(std::size_t nBatchSize, CUdeviceptr pForwardInput, CUdeviceptr pBackwardInput, CUdeviceptr pBackwardOutput, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta) const
	{
		::FullLayer_GPU_backwardBatch(nBatchSize, this->nFanIn, this->nFanOut, pForwardInput, pBackwardInput, pBackwardOutput, pBiasDelta, pWeightDelta, this->pWeight);
	}

	void FullLayer_GPU::update(CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		::updateParam(this->nFanOut, this->nFanIn * this->nFanOut, this->pBias, this->pWeight, pBiasDelta, pWeightDelta);
	}

	void FullLayer_GPU::update(float nFactor, CUdeviceptr pBiasDelta, CUdeviceptr pWeightDelta)
	{
		::updateParamFactor(this->nFanOut, this->nFanIn * this->nFanOut, this->pBias, this->pWeight, pBiasDelta, pWeightDelta, nFactor);
	}
}