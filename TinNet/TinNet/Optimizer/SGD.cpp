
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "SGD.h"

namespace TinNet::Optimizer
{
	SGD::SGD(NN &sNN, std::size_t nNewBatchSize, float nNewLearningRate) :
		OptimizerBase(sNN, nNewBatchSize),
		nLearningRate{nNewLearningRate}
	{
		//Empty.
	}

	SGD::SGD(SGD &&sSrc) :
		OptimizerBase(std::move(sSrc)),
		nLearningRate{sSrc.nLearningRate}
	{
		//Empty.
	}

	void SGD::applyGradient(std::size_t nActualBatchSize, float nGradientFactor)
	{
		auto nFactor{-this->nLearningRate / nActualBatchSize};

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
			this->sNN[nIndex]->update(nFactor * nGradientFactor, this->sBiasDelta[nIndex].data(), this->sWeightDelta[nIndex].data());
	}
}