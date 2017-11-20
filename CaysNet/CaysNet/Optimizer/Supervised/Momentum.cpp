
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#include "Momentum.h"

namespace CaysNet::Optimizer::Supervised
{
	Momentum::Momentum(NN &sNN, std::size_t nBatchSize, float nNewMomentumTerm, float nNewLearningRate) :
		sNN{sNN},
		nBatchSize{nBatchSize},
		nMomentumTerm{nNewMomentumTerm},
		nLearningRate{nNewLearningRate},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())},
		sForwardOutput(sNN.depth()),
		sBackwardOutput(sNN.depth()),
		sActivationInput(sNN.depth()),
		sActivationOutput(sNN.depth()),
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sBiasMomentum{sNN.depth()},
		sWeightMomentum{sNN.depth()},
		sBiasDeltaBuffer(sNN.depth())
	{
		for (std::size_t nIndex{0}, nDepth{sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			auto pLayer{this->sNN[nIndex]};

			this->sForwardOutput[nIndex].resize(nBatchSize);
			this->sBackwardOutput[nIndex].resize(nBatchSize);
			this->sActivationInput[nIndex].resize(nBatchSize);
			this->sActivationOutput[nIndex].resize(nBatchSize);

			std::size_t nActivationInputSize;
			std::size_t nActivationOutputSize;
			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			pLayer->specifySize(nActivationInputSize, nActivationOutputSize, nBiasDeltaSize, nWeightDeltaSize);

			this->sBiasDelta[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightDelta[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBiasMomentum[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightMomentum[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBiasDeltaBuffer[nIndex].resize(nBiasDeltaSize, .0f);

			for (std::size_t nBatch{0}; nBatch < nBatchSize; ++nBatch)
			{
				this->sForwardOutput[nIndex][nBatch].resize(pLayer->fanOut(), .0f);
				this->sBackwardOutput[nIndex][nBatch].resize(pLayer->fanIn(), .0f);
				this->sActivationInput[nIndex][nBatch].resize(pLayer->fanOut(), .0f);
				this->sActivationOutput[nIndex][nBatch].resize(pLayer->fanOut(), .0f);
			}
		}
	}

	Momentum::Momentum(Momentum &&sSrc) :
		sNN{sSrc.sNN},
		nBatchSize{sSrc.nBatchSize},
		nMomentumTerm{sSrc.nMomentumTerm},
		nLearningRate{sSrc.nLearningRate},
		sEngine{std::move(sSrc.sEngine)},
		sForwardOutput{std::move(sSrc.sForwardOutput)},
		sBackwardOutput{std::move(sSrc.sBackwardOutput)},
		sActivationInput{std::move(sSrc.sActivationInput)},
		sActivationOutput{std::move(sSrc.sActivationOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sBiasMomentum{std::move(sSrc.sBiasMomentum)},
		sWeightMomentum{std::move(sSrc.sWeightMomentum)},
		sBiasDeltaBuffer{std::move(sSrc.sBiasDeltaBuffer)}
	{
		//Empty.
	}
}