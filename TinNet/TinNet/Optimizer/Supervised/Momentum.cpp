
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "Momentum.h"

namespace TinNet::Optimizer::Supervised
{
	Momentum::Momentum(NN &sNN, std::size_t nNewBatchSize, float nNewMomentumTerm, float nNewLearningRate) :
		SupervisedOptimizerBase(sNN, nNewBatchSize),
		nMomentumTerm{nNewMomentumTerm},
		nLearningRate{nNewLearningRate},
		sBiasMomentum(sNN.depth()),
		sWeightMomentum(sNN.depth())
	{
		for (std::size_t nIndex{0}, nDepth{sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			this->sNN[nIndex]->specifySize(nBiasDeltaSize, nWeightDeltaSize);

			this->sBiasMomentum[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightMomentum[nIndex].resize(nWeightDeltaSize, .0f);
		}
	}

	Momentum::Momentum(Momentum &&sSrc) :
		SupervisedOptimizerBase(std::move(sSrc)),
		nMomentumTerm{sSrc.nMomentumTerm},
		nLearningRate{sSrc.nLearningRate},
		sBiasMomentum{std::move(sSrc.sBiasMomentum)},
		sWeightMomentum{std::move(sSrc.sWeightMomentum)}
	{
		//Empty.
	}

	void Momentum::applyGradient(std::size_t nActualBatchSize)
	{
		auto nFactor{-this->nLearningRate / nActualBatchSize};

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasMomentum[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
				this->sBiasMomentum[nIndex][nBiasIndex] = this->nMomentumTerm * this->sBiasMomentum[nIndex][nBiasIndex] + nFactor * this->sBiasDelta[nIndex][nBiasIndex];

			for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightMomentum[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
				this->sWeightMomentum[nIndex][nWeightIndex] = this->nMomentumTerm * this->sWeightMomentum[nIndex][nWeightIndex] + nFactor * this->sWeightDelta[nIndex][nWeightIndex];
		}

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
			this->sNN[nIndex]->update(this->sBiasMomentum[nIndex].data(), this->sWeightMomentum[nIndex].data());
	}
}