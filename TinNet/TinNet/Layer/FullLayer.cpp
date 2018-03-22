
/*
	2017.11.03
	Created by AcrylicShrimp.
*/

#include "FullLayer.h"

namespace TinNet::Layer
{
	FullLayer::FullLayer(std::size_t nFanIn, std::size_t nFanOut) :
		Layer(nFanIn, nFanOut),
		sBias(nFanOut, .0f),
		sWeight(nFanOut)
	{
		for (auto &sWeight : this->sWeight)
			sWeight.resize(this->nFanIn);
	}

	FullLayer::FullLayer(const FullLayer &sSrc) :
		Layer(sSrc),
		sBias{sSrc.sBias},
		sWeight{sSrc.sWeight}
	{
		//Empty.
	}

	FullLayer::FullLayer(FullLayer &&sSrc) :
		Layer(sSrc),
		sBias{std::move(sSrc.sBias)},
		sWeight{std::move(sSrc.sWeight)}
	{
		//Empty.
	}

	FullLayer &FullLayer::operator=(const FullLayer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);
		this->sBias = sSrc.sBias;
		this->sWeight = sSrc.sWeight;

		return *this;
	}

	FullLayer &FullLayer::operator=(FullLayer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(std::move(sSrc));
		this->sWeight = std::move(sSrc.sWeight);
		this->sBias = std::move(sSrc.sBias);

		return *this;
	}

	const char *FullLayer::name() const
	{
		return "FullLayer";
	}

	std::unique_ptr<Layer> FullLayer::duplicate() const
	{
		return std::unique_ptr<FullLayer>(new FullLayer(*this));
	}

	void FullLayer::initBias(std::function<float()> sGenerator)
	{
		for (auto &nBias : this->sBias)
			nBias = sGenerator();
	}

	void FullLayer::initWeight(std::function<float()> sGenerator)
	{
		for (auto &sWeightBuffer : this->sWeight)
			for (auto &nWeight : sWeightBuffer)
				nWeight = sGenerator();
	}

	void FullLayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nWeightDeltaSize = this->nFanIn * (nBiasDeltaSize = this->nFanOut);
	}

	void FullLayer::forward(const float *pInput, float *pOutput) const
	{
		//z = X * W + b
		for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
		{
			auto &nDestination{pOutput[nOut] = this->sBias[nOut]};

			for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
				nDestination += pInput[nIn] * this->sWeight[nOut][nIn];
		}
	}

	void FullLayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase) const
	{
		//z = b
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			std::copy(this->sBias.cbegin(), this->sBias.cend(), pOutput[nBatch].begin());

		//z += X * W
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
				for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
					pOutput[nBatch][nOut] += pInput[nBatch][nIn] * this->sWeight[nOut][nIn];
	}

	void FullLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
				pBiasDelta[nOut] += pBackwardInput[nBatch][nOut];

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
				for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
					pWeightDelta[nOut * this->nFanIn + nIn] += pBackwardInput[nBatch][nOut] * pForwardInput[nBatch][nIn];

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
				for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
					pBackwardOutput[nBatch][nIn] += pBackwardInput[nBatch][nOut] * this->sWeight[nOut][nIn];
	}

	void FullLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta, const float *pFactor) const
	{
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
				pBiasDelta[nOut] += pFactor[nBatch] * pBackwardInput[nBatch][nOut];

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
				for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
					pWeightDelta[nOut * this->nFanIn + nIn] += pFactor[nBatch] * pBackwardInput[nBatch][nOut] * pForwardInput[nBatch][nIn];

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
				for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
					pBackwardOutput[nBatch][nIn] += pBackwardInput[nBatch][nOut] * this->sWeight[nOut][nIn];
	}

	void FullLayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
			this->sBias[nOut] += pBiasDelta[nOut];

		for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
			for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
				this->sWeight[nOut][nIn] += pWeightDelta[nOut * this->nFanIn + nIn];
	}

	void FullLayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
			this->sBias[nOut] += nFactor * pBiasDelta[nOut];

		for (std::size_t nOut{0}; nOut < this->nFanOut; ++nOut)
			for (std::size_t nIn{0}; nIn < this->nFanIn; ++nIn)
				this->sWeight[nOut][nIn] += nFactor * pWeightDelta[nOut * this->nFanIn + nIn];
	}

	void FullLayer::serialize(std::ofstream &sOutput) const
	{
		this->Layer::serialize(sOutput);

		for (auto nBias : this->sBias)
			IO::Serializable::write(sOutput, nBias);

		for (auto &sWeight : this->sWeight)
			for (auto nWeight : sWeight)
				IO::Serializable::write(sOutput, nWeight);
	}

	void FullLayer::deserialize(std::ifstream &sInput)
	{
		this->Layer::deserialize(sInput);

		this->sBias.resize(this->nFanOut);
		this->sWeight.resize(this->nFanOut);

		for (auto &nBias : this->sBias)
			nBias = IO::Serializable::read<std::remove_reference_t<decltype(nBias)>>(sInput);

		for (auto &sWeight : this->sWeight)
		{
			sWeight.resize(this->nFanIn);

			for (auto &nWeight : sWeight)
				nWeight = IO::Serializable::read<std::remove_reference_t<decltype(nWeight)>>(sInput);
		}
	}
}