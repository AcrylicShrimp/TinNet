
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "SwishLayer.h"

namespace TinNet::Layer
{
	SwishLayer::SwishLayer(std::size_t nFanIn, float nBeta) :
		Layer(nFanIn, nFanIn),
		nBeta{nBeta}
	{
		//Empty.
	}
	
	SwishLayer::SwishLayer(const SwishLayer &sSrc) :
		Layer(sSrc),
		nBeta{sSrc.nBeta}
	{
		//Empty.
	}
	
	SwishLayer &SwishLayer::operator=(const SwishLayer &sSrc)
	{
		if (&sSrc == this)
			return *this;
		
		this->Layer::operator=(sSrc);
		this->nBeta = sSrc.nBeta;
		
		return *this;
	}

	const char *SwishLayer::name() const
	{
		return "SwishLayer";
	}

	std::unique_ptr<Layer> SwishLayer::duplicate() const
	{
		return std::make_unique<SwishLayer>(*this);
	}

	void SwishLayer::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SwishLayer::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SwishLayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void SwishLayer::forward(const float *pInput, float *pOutput) const
	{
		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			pOutput[nIndex] = pInput[nIndex] / (std::exp(-this->nBeta * pInput[nIndex]) + 1.f);
	}

	void SwishLayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pOutput[nBatch][nIndex] = pInput[nBatch][nIndex] / (std::exp(-this->nBeta * pInput[nBatch][nIndex]) + 1.f);
	}

	void SwishLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			{
				auto nValue{1.f / (std::exp(-this->nBeta * pForwardInput[nBatch][nIndex]) + 1.f)};
				pBackwardOutput[nBatch][nIndex] = pBackwardInput[nBatch][nIndex] * (nValue + this->nBeta * pForwardInput[nBatch][nIndex] * nValue * (1.f - nValue));
			}
	}

	void SwishLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta, const float *pFactor) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			{
				auto nValue{1.f / (std::exp(-this->nBeta * pForwardInput[nBatch][nIndex]) + 1.f)};
				pBackwardOutput[nBatch][nIndex] = pBackwardInput[nBatch][nIndex] * (nValue + this->nBeta * pForwardInput[nBatch][nIndex] * nValue * (1.f - nValue));
			}
	}

	void SwishLayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void SwishLayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}
}