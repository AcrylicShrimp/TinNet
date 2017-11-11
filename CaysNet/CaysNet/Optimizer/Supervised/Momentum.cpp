
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "Momentum.h"

namespace CaysNet::Optimizer::Supervised
{
	Momentum::Momentum(NN &sNN, float nNewMomentumTerm, float nNewLearningRate) :
		nMomentumTerm{nNewMomentumTerm},
		nLearningRate{nNewLearningRate},
		sNN{sNN},
		sActivationInput(sNN.depth()),
		sActivationOutput(sNN.depth()),
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sBiasMomentum{sNN.depth()},
		sWeightMomentum{sNN.depth()},
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
			this->sBiasMomentum[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightMomentum[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBiasDeltaBuffer[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightDeltaBuffer[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBackward[nIndex].resize(pLayer->fanIn(), .0f);
		}
	}

	Momentum::Momentum(Momentum &&sSrc) :
		nMomentumTerm{sSrc.nMomentumTerm},
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sActivationInput{std::move(sSrc.sActivationInput)},
		sActivationOutput{std::move(sSrc.sActivationOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sBiasMomentum{std::move(sSrc.sBiasMomentum)},
		sWeightMomentum{std::move(sSrc.sWeightMomentum)},
		sBiasDeltaBuffer{std::move(sSrc.sBiasDeltaBuffer)},
		sWeightDeltaBuffer{std::move(sSrc.sWeightDeltaBuffer)},
		sBackward{std::move(sSrc.sBackward)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}
}