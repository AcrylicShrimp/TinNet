
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "OptimizerBase_GPU.h"

namespace TinNet::Optimizer
{
	OptimizerBase_GPU::OptimizerBase_GPU(NN_GPU &sNN, std::size_t nNewBatchSize) :
		sNN{sNN},
		nBatchSize{nNewBatchSize},
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sBackwardInput{nNewBatchSize * this->sNN.layer().back()->fanOut()},
		sForwardOutput(sNN.depth()),
		sBackwardOutput(sNN.depth())
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			const auto &pLayer{this->sNN[nIndex]};

			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			pLayer->specifySize(nBiasDeltaSize, nWeightDeltaSize);

			this->sBiasDelta[nIndex].resize(nNewBatchSize * nBiasDeltaSize);
			this->sWeightDelta[nIndex].resize(nNewBatchSize * nWeightDeltaSize);
			this->sForwardOutput[nIndex].resize(nNewBatchSize * pLayer->fanOut());
			this->sBackwardOutput[nIndex].resize(nNewBatchSize * pLayer->fanIn());
		}
	}
}