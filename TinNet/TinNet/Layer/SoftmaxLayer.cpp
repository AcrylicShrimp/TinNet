
/*
	2018.01.14
	Created by AcrylicShrimp.
*/

#include "SoftmaxLayer.h"

namespace TinNet::Layer
{
	SoftmaxLayer::SoftmaxLayer(std::size_t nFanIn) :
		Layer(nFanIn, nFanIn),
		sOutput(nFanIn, .0f)
	{
		//Empty.
	}

	SoftmaxLayer::SoftmaxLayer(const SoftmaxLayer &sSrc) :
		Layer(sSrc),
		sOutput(sSrc.sOutput)
	{
		//Empty.
	}

	SoftmaxLayer::SoftmaxLayer(SoftmaxLayer &&sSrc) :
		Layer(sSrc),
		sOutput(std::move(sSrc.sOutput))
	{
		//Empty.
	}

	SoftmaxLayer &SoftmaxLayer::operator=(const SoftmaxLayer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);
		this->sOutput = sSrc.sOutput;

		return *this;
	}

	SoftmaxLayer &SoftmaxLayer::operator=(SoftmaxLayer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);
		this->sOutput = std::move(sSrc.sOutput);

		return *this;
	}

	const char *SoftmaxLayer::name() const
	{
		return "SoftmaxLayer";
	}

	std::unique_ptr<Layer> SoftmaxLayer::duplicate() const
	{
		return std::make_unique<SoftmaxLayer>(*this);
	}

	void SoftmaxLayer::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SoftmaxLayer::initWeight(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void SoftmaxLayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = nWeightDeltaSize = 0;
	}

	void SoftmaxLayer::forward(const float *pInput, float *pOutput) const
	{
		//Desk[0] : Max output
		//Desk[1] : Accumulator
		float vDesk[2]{pInput[0], pInput[0]};

		//Find max value.
		for (std::size_t nIndex{1}; nIndex < this->nFanIn; ++nIndex)
		{
			vDesk[1] = pInput[nIndex];
			vDesk[0] = vDesk[vDesk[1] > vDesk[0]];
		}

		//Clear the accumulator.
		vDesk[1] = .0f;

		//Accumulate and fill.
		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			vDesk[1] += (pOutput[nIndex] = std::exp(pInput[nIndex] - vDesk[0]));

		//Divide by the accumulated value.
		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			pOutput[nIndex] /= vDesk[1];
	}

	void SoftmaxLayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
		{
			//Desk[0] : Max output
			//Desk[1] : Accumulator
			float vDesk[2]{pInput[nBatch][0], pInput[nBatch][0]};

			//Find max value.
			for (std::size_t nIndex{1}; nIndex < this->nFanIn; ++nIndex)
			{
				vDesk[1] = pInput[nBatch][nIndex];
				vDesk[0] = vDesk[vDesk[1] > vDesk[0]];
			}

			//Clear the accumulator.
			vDesk[1] = .0f;

			//Accumulate and fill.
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				vDesk[1] += (pOutput[nBatch][nIndex] = std::exp(pInput[nBatch][nIndex] - vDesk[0]));

			//Divide by the accumulated value.
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pOutput[nBatch][nIndex] /= vDesk[1];
		}
	}

	void SoftmaxLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
		{
			this->forward(pForwardInput[nBatch].data(), this->sOutput.data());

			for (std::size_t nFirst{0}; nFirst < this->nFanIn; ++nFirst)
				for (std::size_t nSecond{0}; nSecond < this->nFanIn; ++nSecond)
					pBackwardOutput[nBatch][nFirst] += pBackwardInput[nBatch][nSecond] * (nFirst == nSecond ? this->sOutput[nSecond] * (1.f - this->sOutput[nSecond]) : -this->sOutput[nSecond] * this->sOutput[nFirst]);
		}
	}

	void SoftmaxLayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void SoftmaxLayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		//Empty.
	}

	void SoftmaxLayer::deserialize(std::ifstream &sInput)
	{
		this->Layer::deserialize(sInput);
		this->sOutput.resize(this->nFanIn);
	}
}