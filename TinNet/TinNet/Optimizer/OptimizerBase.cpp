
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "OptimizerBase.h"

namespace TinNet::Optimizer
{
	OptimizerBase::OptimizerBase(NN &sNN, std::size_t nNewBatchSize) :
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

	OptimizerBase::OptimizerBase(OptimizerBase &&sSrc) :
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

	void OptimizerBase::computeGradient(std::size_t nSize, const std::vector<float> *pInput, const std::vector<float> *pOutput, std::function<const float *(std::size_t, std::vector<std::vector<float>> &, std::vector<std::vector<float>> &)> fBefore, std::function<void(std::size_t)> fAfter)
	{
		auto nDimension{pOutput->size()};
		auto nActualBatchSize{std::min(this->nBatchSize, nSize)};

		//Initialize the delta buffers.
		OptimizerHelper::zeros(this->sBiasDelta);
		OptimizerHelper::zeros(this->sWeightDelta);
		OptimizerHelper::zeros(this->sBackwardOutput);

		//Forward.
		this->sNN.forward(
			nActualBatchSize,
			pInput,
			this->sForwardOutput.data(),
			true);

		auto pFactor{fBefore(nActualBatchSize, this->sForwardOutput.back(), this->sBackwardInput)};

		//Backward.
		this->sNN.backward(
			nActualBatchSize,
			pInput,
			this->sBackwardInput.data(),
			this->sForwardOutput.data(),
			this->sBackwardOutput.data(),
			this->sBiasDelta.data(),
			this->sWeightDelta.data(),
			pFactor);

		fAfter(nActualBatchSize);
	}
}