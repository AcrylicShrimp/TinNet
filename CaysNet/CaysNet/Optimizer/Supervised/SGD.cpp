
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "SGD.h"

namespace CaysNet::Optimizer::Supervised
{
	SGD::SGD(NN &sNN, float nNewLearningRate) :
		nLearningRate{nNewLearningRate},
		sNN{sNN},
		sActivationInput(sNN.depth()),
		sActivationOutput(sNN.depth()),
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sBiasDeltaBuffer(sNN.depth()),
		sWeightDeltaBuffer(sNN.depth()),
		sBackward(sNN.depth()),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			auto pLayer{this->sNN[nIndex]};

			std::size_t nActivationInputSize;
			std::size_t nActivationOutputSize;
			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			pLayer->specifySize(nActivationInputSize, nActivationOutputSize, nBiasDeltaSize, nWeightDeltaSize);

			this->sActivationInput[nIndex].resize(nActivationInputSize, .0f);
			this->sActivationOutput[nIndex].resize(nActivationOutputSize, .0f);
			this->sBiasDelta[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightDelta[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBiasDeltaBuffer[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightDeltaBuffer[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBackward[nIndex].resize(pLayer->fanIn(), .0f);
		}
	}

	SGD::SGD(SGD &&sSrc) :
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sActivationInput{std::move(sSrc.sActivationInput)},
		sActivationOutput{std::move(sSrc.sActivationOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sBiasDeltaBuffer{std::move(sSrc.sBiasDeltaBuffer)},
		sWeightDeltaBuffer{std::move(sSrc.sWeightDeltaBuffer)},
		sBackward{std::move(sSrc.sBackward)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}
}