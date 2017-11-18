
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "Momentum.h"

namespace CaysNet::Optimizer::Supervised
{
	Momentum::Momentum(NN &sNN, std::size_t nNewBatchSize, float nNewMomentumTerm, float nNewLearningRate) :
		sNN{sNN},
		nBatchSize{nNewBatchSize},
		nMomentumTerm{nNewMomentumTerm},
		nLearningRate{nNewLearningRate},
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sBiasDeltaBuffer(sNN.depth()),
		sWeightDeltaBuffer(sNN.depth()),
		sBiasMomentum(sNN.depth()),
		sWeightMomentum(sNN.depth()),
		sForwardOutput(sNN.depth()),
		sBackwardOutput(sNN.depth()),
		sActivationInput(sNN.depth()),
		sActivationOutput(sNN.depth()),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			//this->sForwardOutput[nIndex].resize(nNewBatchSize);
			//this->sBackwardOutput[nIndex].resize(nNewBatchSize);
			//this->sActivationInput[nIndex].resize(nNewBatchSize);
			//this->sActivationOutput[nIndex].resize(nNewBatchSize);

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
			this->sBiasMomentum[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightMomentum[nIndex].resize(nWeightDeltaSize, .0f);

			//Old
			this->sForwardOutput[nIndex].resize(pLayer->fanOut());
			this->sBackwardOutput[nIndex].resize(pLayer->fanIn());
			this->sActivationInput[nIndex].resize(nActivationInputSize);
			this->sActivationOutput[nIndex].resize(nActivationOutputSize);

			//for (std::size_t nBatchIndex{0}; nBatchIndex < nNewBatchSize; ++nBatchIndex)
			//{
			//	this->sForwardOutput[nIndex][nBatchIndex].resize(pLayer->fanOut());
			//	this->sBackwardOutput[nIndex][nBatchIndex].resize(pLayer->fanIn());
			//	this->sActivationInput[nIndex][nBatchIndex].resize(nActivationInputSize);
			//	this->sActivationOutput[nIndex][nBatchIndex].resize(nActivationOutputSize);
			//}
		}
	}

	Momentum::Momentum(Momentum &&sSrc) :
		sNN{sSrc.sNN},
		nBatchSize{sSrc.nBatchSize},
		nMomentumTerm{sSrc.nMomentumTerm},
		nLearningRate{sSrc.nLearningRate},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sBiasDeltaBuffer{std::move(sSrc.sBiasDeltaBuffer)},
		sBiasMomentum{std::move(sSrc.sBiasMomentum)},
		sWeightMomentum{std::move(sSrc.sWeightMomentum)},
		sForwardOutput{std::move(sSrc.sForwardOutput)},
		sBackwardOutput{std::move(sSrc.sBackwardOutput)},
		sActivationInput{std::move(sSrc.sActivationInput)},
		sActivationOutput{std::move(sSrc.sActivationOutput)},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}
}