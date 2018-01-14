
/*
	2018.01.14
	Created by AcrylicShrimp.
*/

#include "ReLULayer.h"

namespace CaysNet::Layer
{
	ReLULayer::ReLULayer(std::size_t nFanIn) :
		Layer(nFanIn, nFanIn)
	{
		//Empty.
	}

	ReLULayer::ReLULayer(const ReLULayer &sSrc) :
		Layer(sSrc)
	{
		//Empty.
	}

	ReLULayer &ReLULayer::operator=(const ReLULayer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);

		return *this;
	}

	std::unique_ptr<Layer> ReLULayer::duplicate() const
	{
		return std::make_unique<ReLULayer>(this->nFanIn);
	}

	void ReLULayer::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void ReLULayer::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void ReLULayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void ReLULayer::forward(const float *pInput, float *pOutput) const
	{
		static constexpr float vDesk[2]{.0f, 1.f};

		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			pOutput[nIndex] = vDesk[pInput[nIndex] > .0f] * pInput[nIndex];
	}

	void ReLULayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput) const
	{
		static constexpr float vDesk[2]{.0f, 1.f};

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pOutput[nBatch][nIndex] = vDesk[pInput[nBatch][nIndex] > .0f] * pInput[nBatch][nIndex];
	}

	void ReLULayer::backward(const float *pForwardInput, const float *pBackwardInput, float *pBackwardOutput, float *pWeightDelta) const
	{
		static constexpr float vDesk[2]{.0f, 1.f};

		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			pBackwardOutput[nIndex] = pBackwardInput[nIndex] * vDesk[pForwardInput[nIndex] > .0f];
	}

	void ReLULayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pWeightDelta) const
	{
		static constexpr float vDesk[2]{.0f, 1.f};

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pBackwardOutput[nBatch][nIndex] = pBackwardInput[nBatch][nIndex] * vDesk[pForwardInput[nBatch][nIndex] > .0f];
	}

	void ReLULayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void ReLULayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void ReLULayer::serialize(std::ofstream &sOutput) const
	{
		IO::Serializable::write(sOutput, this->nFanIn);
	}

	void ReLULayer::deserialize(std::ifstream &sInput)
	{
		this->nFanIn = this->nFanOut = IO::Serializable::read<std::size_t>(sInput);
	}
}