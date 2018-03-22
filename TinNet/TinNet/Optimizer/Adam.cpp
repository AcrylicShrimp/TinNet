
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "Adam.h"

namespace TinNet::Optimizer
{
	Adam::Adam(NN &sNN, std::size_t nNewBatchSize, float nNewLearningRate, float nNewBeta1, float nNewBeta2) :
		OptimizerBase(sNN, nNewBatchSize),
		nLearningRate{nNewLearningRate},
		nBeta1{nNewBeta1},
		nBeta2{nNewBeta2},
		sBiasBeta1(sNN.depth()),
		sWeightBeta1(sNN.depth()),
		sBiasBeta2(sNN.depth()),
		sWeightBeta2(sNN.depth())
	{
		for (std::size_t nIndex{0}, nDepth{sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			this->sNN[nIndex]->specifySize(nBiasDeltaSize, nWeightDeltaSize);

			this->sBiasBeta1[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightBeta1[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBiasBeta2[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightBeta2[nIndex].resize(nWeightDeltaSize, .0f);
		}
	}
	
	Adam::Adam(Adam &&sSrc) :
		OptimizerBase(std::move(sSrc)),
		nLearningRate{sSrc.nLearningRate},
		nBeta1{sSrc.nBeta1},
		nBeta2{sSrc.nBeta2},
		sBiasBeta1{std::move(sSrc.sBiasBeta1)},
		sWeightBeta1{std::move(sSrc.sWeightBeta1)},
		sBiasBeta2{std::move(sSrc.sBiasBeta2)},
		sWeightBeta2{std::move(sSrc.sWeightBeta2)}
	{
		//Empty.
	}

	void Adam::applyGradient(std::size_t nActualBatchSize, float nGradientFactor)
	{
		const auto nDivisor{nGradientFactor / nActualBatchSize};

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
				this->sBiasBeta1[nIndex][nBiasIndex] = this->nBeta1 * this->sBiasBeta1[nIndex][nBiasIndex] + (1.f - this->nBeta1) * this->sBiasDelta[nIndex][nBiasIndex] * nDivisor;

			for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
				this->sWeightBeta1[nIndex][nWeightIndex] = this->nBeta1 * this->sWeightBeta1[nIndex][nWeightIndex] + (1.f - this->nBeta1) * this->sWeightDelta[nIndex][nWeightIndex] * nDivisor;
		}

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
				this->sBiasBeta2[nIndex][nBiasIndex] = this->nBeta2 * this->sBiasBeta2[nIndex][nBiasIndex] + (1.f - this->nBeta2) * this->sBiasDelta[nIndex][nBiasIndex] * nDivisor * this->sBiasDelta[nIndex][nBiasIndex] * nDivisor;

			for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
				this->sWeightBeta2[nIndex][nWeightIndex] = this->nBeta2 * this->sWeightBeta2[nIndex][nWeightIndex] + (1.f - this->nBeta2) * this->sWeightDelta[nIndex][nWeightIndex] * nDivisor * this->sWeightDelta[nIndex][nWeightIndex] * nDivisor;
		}

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
				this->sBiasDelta[nIndex][nBiasIndex] = -this->nLearningRate * (this->sBiasBeta1[nIndex][nBiasIndex] / (1.f - this->nBeta1)) / (std::sqrt(this->sBiasBeta2[nIndex][nBiasIndex] / (1.f - this->nBeta2)) + 1e-4f);

			for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
				this->sWeightDelta[nIndex][nWeightIndex] = -this->nLearningRate * (this->sWeightBeta1[nIndex][nWeightIndex] / (1.f - this->nBeta1)) / (std::sqrt(this->sWeightBeta2[nIndex][nWeightIndex] / (1.f - this->nBeta2)) + 1e-4f);
		}

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
			this->sNN[nIndex]->update(this->sBiasDelta[nIndex].data(), this->sWeightDelta[nIndex].data());
	}
}