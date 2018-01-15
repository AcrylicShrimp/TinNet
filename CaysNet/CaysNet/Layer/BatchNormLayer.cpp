
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "BatchNormLayer.h"

namespace CaysNet::Layer
{
	BatchNormLayer::BatchNormLayer(std::size_t nFanIn, float nNewMomentum) :
		Layer(nFanIn, nFanIn),
		nMomentum(nNewMomentum),
		sShift(nFanIn, .0f),
		sScale(nFanIn, .0f),
		sMean(nFanIn, .0f),
		sVariance(nFanIn, .0f),
		sMeanBuffer(nFanIn, .0f),
		sVarianceBuffer(nFanIn, .0f),
		sVarianceInversed(nFanIn, .0f)
	{
		//Empty.
	}

	BatchNormLayer::BatchNormLayer(const BatchNormLayer &sSrc) :
		Layer(sSrc),
		nMomentum(sSrc.nMomentum),
		sShift(sSrc.sShift),
		sScale(sSrc.sScale),
		sMean(sSrc.sMean),
		sVariance(sSrc.sVariance),
		sMeanBuffer(sSrc.sMeanBuffer),
		sVarianceBuffer(sSrc.sVarianceBuffer),
		sVarianceInversed(sSrc.sVarianceInversed)
	{
		//Empty.
	}

	BatchNormLayer::BatchNormLayer(BatchNormLayer &&sSrc) :
		Layer(sSrc),
		nMomentum(sSrc.nMomentum),
		sShift(std::move(sSrc.sShift)),
		sScale(std::move(sSrc.sScale)),
		sMean(std::move(sSrc.sMean)),
		sVariance(std::move(sSrc.sVariance)),
		sMeanBuffer(std::move(sSrc.sMeanBuffer)),
		sVarianceBuffer(std::move(sSrc.sVarianceBuffer)),
		sVarianceInversed(std::move(sSrc.sVarianceInversed))
	{
		//Empty.
	}

	BatchNormLayer &BatchNormLayer::operator=(const BatchNormLayer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);
		this->nMomentum = sSrc.nMomentum;
		this->sShift = sSrc.sShift;
		this->sScale = sSrc.sScale;
		this->sMean = sSrc.sMean;
		this->sVariance = sSrc.sVariance;
		this->sMeanBuffer = sSrc.sMeanBuffer;
		this->sVarianceBuffer = sSrc.sVarianceBuffer;
		this->sVarianceInversed = sSrc.sVarianceInversed;

		return *this;
	}

	BatchNormLayer &BatchNormLayer::operator=(BatchNormLayer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Layer::operator=(sSrc);
		this->nMomentum = sSrc.nMomentum;
		this->sShift = std::move(sSrc.sShift);
		this->sScale = std::move(sSrc.sScale);
		this->sMean = std::move(sSrc.sMean);
		this->sVariance = std::move(sSrc.sVariance);
		this->sMeanBuffer = std::move(sSrc.sMeanBuffer);
		this->sVarianceBuffer = std::move(sSrc.sVarianceBuffer);
		this->sVarianceInversed = std::move(sSrc.sVarianceInversed);

		return *this;
	}

	std::unique_ptr<Layer> BatchNormLayer::duplicate() const
	{
		return std::unique_ptr<BatchNormLayer>(new BatchNormLayer(this->nFanIn, this->nFanOut));
	}

	void BatchNormLayer::initBias(std::function<float()> sGenerator)
	{
		//Empty.
	}

	void BatchNormLayer::initWeight(std::function<float()> sGenerator)
	{
		for (auto &nShift : this->sShift)
			nShift = sGenerator();

		for (auto &nScale : this->sScale)
			nScale = sGenerator();
	}

	void BatchNormLayer::specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const
	{
		nBiasDeltaSize = 0;
		nWeightDeltaSize = this->nFanIn * this->nFanIn;
	}

	void BatchNormLayer::forward(const float *pInput, float *pOutput) const
	{
		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			pOutput[nIndex] = this->sShift[nIndex] + this->sScale[nIndex] * (pInput[nIndex] - this->sMean[nIndex]) / std::sqrt(this->sVariance[nIndex] + 1e-4f);
	}

	void BatchNormLayer::forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput) const
	{
		//Compute the mini-batch mean.
		std::fill(this->sMeanBuffer.begin(), this->sMeanBuffer.end(), .0f);

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				this->sMeanBuffer[nIndex] += pInput[nBatch][nIndex];

		const auto nFactor{1.f / nBatchSize};

		for (auto &nValue : this->sMeanBuffer)
			nValue *= nFactor;

		std::fill(this->sVarianceBuffer.begin(), this->sVarianceBuffer.end(), .0f);

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				this->sVarianceBuffer[nIndex] += (pInput[nBatch][nIndex] - this->sMeanBuffer[nIndex]) * (pInput[nBatch][nIndex] - this->sMeanBuffer[nIndex]);

		for (auto &nValue : this->sVarianceBuffer)
			nValue *= nFactor;

		//Update!
		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
		{
			this->sMean[nIndex] = this->nMomentum * this->sMean[nIndex] + (1.f - this->nMomentum) * this->sMeanBuffer[nIndex];
			this->sVariance[nIndex] = this->nMomentum * this->sVariance[nIndex] + (1.f - this->nMomentum) * this->sVarianceBuffer[nIndex];
			this->sVarianceInversed[nIndex] = 1.f / std::sqrt(this->sVarianceBuffer[nIndex] + 1e-4f);
		}

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pOutput[nBatch][nIndex] = this->sShift[nIndex] + this->sScale[nIndex] * (pInput[nBatch][nIndex] - this->sMeanBuffer[nIndex]) * this->sVarianceInversed[nIndex];
	}

	void BatchNormLayer::backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pWeightDelta) const
	{
		//Shift delta
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pWeightDelta[nIndex] += pBackwardInput[nBatch][nIndex];

		//Scale delta
		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pWeightDelta[this->nFanIn + nIndex] += pBackwardInput[nBatch][nIndex] * (pForwardInput[nBatch][nIndex] - this->sMeanBuffer[nIndex]) * this->sVarianceInversed[nIndex];

		const auto nFactor{nBatchSize};
		const auto nFactorInv{1.f / nBatchSize};

		std::vector<std::vector<float>> sDInputHat(nBatchSize);
		std::vector<float> sDInputHatSum(this->nFanIn, .0f);
		std::vector<float> sDInputHatMulSum(this->nFanIn, .0f);

		for (auto &sVector : sDInputHat)
			sVector.resize(this->nFanIn);

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				sDInputHat[nBatch][nIndex] = pBackwardInput[nBatch][nIndex] * this->sScale[nIndex];

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
			{
				sDInputHatSum[nIndex] += sDInputHat[nBatch][nIndex];
				sDInputHatMulSum[nIndex] += sDInputHat[nBatch][nIndex] * (pForwardInput[nBatch][nIndex] - this->sMeanBuffer[nIndex]) * this->sVarianceInversed[nIndex];
			}

		for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
				pBackwardOutput[nBatch][nIndex] = nFactorInv * this->sVarianceInversed[nIndex] * (nFactor * sDInputHat[nBatch][nIndex] - sDInputHatSum[nIndex] - (pForwardInput[nBatch][nIndex] - this->sMeanBuffer[nIndex]) * this->sVarianceInversed[nIndex] * sDInputHatMulSum[nIndex]);
	}

	void BatchNormLayer::update(const float *pBiasDelta, const float *pWeightDelta)
	{
		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
		{
			this->sShift[nIndex] += pWeightDelta[nIndex];
			this->sScale[nIndex] += pWeightDelta[this->nFanIn + nIndex];
		}
	}

	void BatchNormLayer::update(float nFactor, const float *pBiasDelta, const float *pWeightDelta)
	{
		for (std::size_t nIndex{0}; nIndex < this->nFanIn; ++nIndex)
		{
			this->sShift[nIndex] += nFactor * pWeightDelta[nIndex];
			this->sScale[nIndex] += nFactor * pWeightDelta[this->nFanIn + nIndex];
		}
	}

	void BatchNormLayer::serialize(std::ofstream &sOutput) const
	{
		//Empty.
	}

	void BatchNormLayer::deserialize(std::ifstream &sInput)
	{
		//Empty.
	}
}