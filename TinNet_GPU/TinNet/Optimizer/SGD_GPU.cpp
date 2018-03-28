
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "SGD_GPU.h"

namespace TinNet::Optimizer
{
	SGD_GPU::SGD_GPU(NN_GPU &sNN, std::size_t nNewBatchSize, float nNewLearningRate) :
		OptimizerBase_GPU(sNN, nNewBatchSize),
		nLearningRate{nNewLearningRate}
	{
		//Empty.
	}

	void SGD_GPU::applyGradient(std::size_t nActualBatchSize, float nGradientFactor)
	{
		auto nFactor{-this->nLearningRate / nActualBatchSize * nGradientFactor};

		for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
			this->sNN[nIndex]->update(nFactor, this->sBiasDelta[nIndex], this->sWeightDelta[nIndex]);
	}
}