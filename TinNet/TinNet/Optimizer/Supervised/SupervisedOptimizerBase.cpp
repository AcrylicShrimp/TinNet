
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "SupervisedOptimizerBase.h"

namespace TinNet::Optimizer::Supervised
{
	SupervisedOptimizerBase::SupervisedOptimizerBase(NN &sNN, std::size_t nNewBatchSize) :
		sNN{sNN},
		nBatchSize{nNewBatchSize},
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sBackwardInput(nNewBatchSize),
		sForwardOutput(sNN.depth()),
		sBackwardOutput(sNN.depth()),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nBatchIndex{0}; nBatchIndex < nNewBatchSize; ++nBatchIndex)
			this->sBackwardInput[nBatchIndex].resize(this->sNN.layer().back()->fanOut());

		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			this->sForwardOutput[nIndex].resize(nNewBatchSize);
			this->sBackwardOutput[nIndex].resize(nNewBatchSize);

			const auto &pLayer{this->sNN[nIndex]};

			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			pLayer->specifySize(nBiasDeltaSize, nWeightDeltaSize);

			this->sBiasDelta[nIndex].resize(nBiasDeltaSize);
			this->sWeightDelta[nIndex].resize(nWeightDeltaSize);

			for (std::size_t nBatchIndex{0}; nBatchIndex < nNewBatchSize; ++nBatchIndex)
			{
				this->sForwardOutput[nIndex][nBatchIndex].resize(pLayer->fanOut());
				this->sBackwardOutput[nIndex][nBatchIndex].resize(pLayer->fanIn());
			}
		}
	}
	
	SupervisedOptimizerBase::SupervisedOptimizerBase(SupervisedOptimizerBase &&sSrc) :
		sNN{sSrc.sNN},
		nBatchSize{sSrc.nBatchSize},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sBackwardInput{std::move(sSrc.sBackwardInput)},
		sForwardOutput{std::move(sSrc.sForwardOutput)},
		sBackwardOutput{std::move(sSrc.sBackwardOutput)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}
}