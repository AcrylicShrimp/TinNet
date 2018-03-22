
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "RMSProp.h"

namespace TinNet::Optimizer
{
	RMSProp::RMSProp(NN &sNN, std::size_t nNewBatchSize, float nNewDecay, float nNewLearningRate) :
		OptimizerBase(sNN, nNewBatchSize),
		nDecay{nNewDecay},
		nLearningRate{nNewLearningRate},
		sBiasRate(sNN.depth()),
		sWeightRate(sNN.depth())
	{
		for (std::size_t nIndex{0}, nDepth{sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			this->sNN[nIndex]->specifySize(nBiasDeltaSize, nWeightDeltaSize);

			this->sBiasRate[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightRate[nIndex].resize(nWeightDeltaSize, .0f);
		}
	}
	
	RMSProp::RMSProp(RMSProp &&sSrc) :
		OptimizerBase(std::move(sSrc)),
		nDecay{sSrc.nDecay},
		nLearningRate{sSrc.nLearningRate},
		sBiasRate{std::move(sSrc.sBiasRate)},
		sWeightRate{std::move(sSrc.sWeightRate)}
	{
		//Empty.
	}

	void RMSProp::applyGradient(std::size_t nActualBatchSize, float nGradientFactor)
	{
		const auto nDivisor{nGradientFactor / nActualBatchSize};

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
				this->sBiasRate[nIndex][nBiasIndex] = this->nDecay * this->sBiasRate[nIndex][nBiasIndex] + (1.f - this->nDecay) * (this->sBiasDelta[nIndex][nBiasIndex] * nDivisor) * (this->sBiasDelta[nIndex][nBiasIndex] * nDivisor);

			for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
				this->sWeightRate[nIndex][nWeightIndex] = this->nDecay * this->sWeightRate[nIndex][nWeightIndex] + (1.f - this->nDecay) * (this->sWeightDelta[nIndex][nWeightIndex] * nDivisor) * (this->sWeightDelta[nIndex][nWeightIndex] * nDivisor);
		}

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
				this->sBiasDelta[nIndex][nBiasIndex] *= -this->nLearningRate / std::sqrt(this->sBiasRate[nIndex][nBiasIndex] + 1e-4f);

			for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
				this->sWeightDelta[nIndex][nWeightIndex] *= -this->nLearningRate / std::sqrt(this->sWeightRate[nIndex][nWeightIndex] + 1e-4f);
		}

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
			this->sNN[nIndex]->update(this->sBiasDelta[nIndex].data(), this->sWeightDelta[nIndex].data());
	}
}