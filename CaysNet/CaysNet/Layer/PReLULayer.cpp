
/*
	2018.01.14
	Created by AcrylicShrimp.
*/

#include "PReLULayer.h"

namespace CaysNet::Layer
{
	PReLULayer::PReLULayer(std::size_t nFanIn, float nParam) :
		Layer(nFanIn, nFanIn),
		nParam{nParam}
	{
		//Empty.
	}
	
	PReLULayer::PReLULayer(const PReLULayer &sSrc) :
		Layer(sSrc),
		nParam{sSrc.nParam}
	{
		//Empty.
	}
	
	PReLULayer &PReLULayer::operator=(const PReLULayer &sSrc)
	{
		if (&sSrc == this)
			return *this;
		
		this->Layer::operator=(sSrc);
		this->nParam = sSrc.nParam;
		
		return *this;
	}
	
	const char *PReLULayer::name() const
	{
		return "PReLULayer";
	}

	std::unique_ptr<Layer> PReLULayer::duplicate() const
	{
		return std::make_unique<PReLULayer>(*this);
	}

	void PReLULayer::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void PReLULayer::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void PReLULayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void PReLULayer::forward(const float *pInput, float *pOutput) const
	{
		float vDesk[2]{this->nParam, 1.f};

		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			pOutput[nIndex] = vDesk[pInput[nIndex] > .0f] * pInput[nIndex];
	}

	void PReLULayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase) const
	{
		float vDesk[2]{this->nParam, 1.f};

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pOutput[nBatch][nIndex] = vDesk[pInput[nBatch][nIndex] > .0f] * pInput[nBatch][nIndex];
	}

	void PReLULayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pWeightDelta) const
	{
		float vDesk[2]{this->nParam, 1.f};

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pBackwardOutput[nBatch][nIndex] = pBackwardInput[nBatch][nIndex] * vDesk[pForwardInput[nBatch][nIndex] > .0f];
	}

	void PReLULayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void PReLULayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void PReLULayer::serialize(std::ofstream &sOutput) const
	{
		this->Layer::serialize(sOutput);
		IO::Serializable::write(sOutput, this->nParam);
	}

	void PReLULayer::deserialize(std::ifstream &sInput)
	{
		this->Layer::deserialize(sInput);
		this->nParam = IO::Serializable::read<std::remove_reference_t<decltype(nParam)>>(sInput);
	}
}