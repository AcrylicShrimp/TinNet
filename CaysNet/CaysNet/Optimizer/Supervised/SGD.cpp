
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "SGD.h"

namespace CaysNet::Optimizer::Supervised
{
	SGD::SGD(NN &sNN, std::size_t nNewBatchSize, float nNewLearningRate) :
		sNN{sNN},
		nBatchSize{nNewBatchSize},
		nLearningRate{nNewLearningRate},
		sBiasDelta(this->sNN.depth()),
		sWeightDelta(this->sNN.depth()),
		sBiasDeltaBuffer(this->sNN.depth()),
		sWeightDeltaBuffer(this->sNN.depth()),
		sForwardOutput(this->sNN.depth()),
		sBackwardOutput(this->sNN.depth()),
		sActivationInput(this->sNN.depth()),
		sActivationOutput(this->sNN.depth()),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			sForwardOutput[nIndex].resize(nNewBatchSize);
			sBackwardOutput[nIndex].resize(nNewBatchSize);
			sActivationInput[nIndex].resize(nNewBatchSize);
			sActivationOutput[nIndex].resize(nNewBatchSize);

			auto pLayer{this->sNN[nIndex]};

			std::size_t nActivationInputSize;
			std::size_t nActivationOutputSize;
			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			pLayer->specifySize(nActivationInputSize, nActivationOutputSize, nBiasDeltaSize, nWeightDeltaSize);

			this->sBiasDelta[nIndex].resize(nBiasDeltaSize);
			this->sWeightDelta[nIndex].resize(nWeightDeltaSize);
			this->sBiasDeltaBuffer[nIndex].resize(nBiasDeltaSize);
			this->sWeightDeltaBuffer[nIndex].resize(nWeightDeltaSize);

			for (std::size_t nBatchIndex{0}; nBatchIndex < nNewBatchSize; ++nBatchIndex)
			{
				sForwardOutput[nIndex][nBatchIndex].resize(pLayer->fanOut());
				sBackwardOutput[nIndex][nBatchIndex].resize(pLayer->fanIn());
				sActivationInput[nIndex][nBatchIndex].resize(nActivationInputSize);
				sActivationOutput[nIndex][nBatchIndex].resize(nActivationOutputSize);
			}
		}
	}

	SGD::SGD(SGD &&sSrc) :
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}
}