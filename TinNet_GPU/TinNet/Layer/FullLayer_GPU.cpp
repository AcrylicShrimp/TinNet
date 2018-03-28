
/*
	2018.01.19
	Created by AcrylicShrimp.
*/

#include "FullLayer_GPU.h"

namespace TinNet::Layer
{
	FullLayer_GPU::FullLayer_GPU(std::size_t nFanIn, std::size_t nFanOut) :
		Layer_GPU(nFanIn, nFanOut),
		sBias{nFanOut},
		sWeight{nFanIn * nFanOut}
	{
		//Empty.
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

		this->sBias = sBias;
	}

	void FullLayer_GPU::initWeight(std::function<float()> sGenerator)
	{
		std::vector<float> sWeight(this->nFanIn * this->nFanOut);

		for (auto &nWeight : sWeight)
			nWeight = sGenerator();

		this->sWeight = sWeight;
	}

	void FullLayer_GPU::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nWeightDeltaSize = this->nFanIn * (nBiasDeltaSize = this->nFanOut);
	}

	void FullLayer_GPU::forward(const GPUVector &sInput, GPUVector &sOutput) const
	{
		::FullLayer_GPU_forward(this->nFanIn, this->nFanOut, sInput, sOutput, this->sBias, this->sWeight);
	}

	void FullLayer_GPU::forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const
	{
		::FullLayer_GPU_forwardBatch(nIndex, nBatchSize, this->nFanIn, this->nFanOut, sInput, sOutput, this->sBias, this->sWeight);
	}

	void FullLayer_GPU::backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const
	{
		::FullLayer_GPU_backwardBatch(nIndex, nBatchSize, this->nFanIn, this->nFanOut, sForwardInput, sBackwardInput, sBackwardOutput, sBiasDelta, sWeightDelta, this->sWeight);
	}

	void FullLayer_GPU::update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		::updateParam(this->nFanOut, this->nFanIn * this->nFanOut, this->sBias, this->sWeight, sBiasDelta, sWeightDelta);
	}

	void FullLayer_GPU::update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta)
	{
		::updateParamFactor(this->nFanOut, this->nFanIn * this->nFanOut, this->sBias, this->sWeight, sBiasDelta, sWeightDelta, nFactor);
	}
}