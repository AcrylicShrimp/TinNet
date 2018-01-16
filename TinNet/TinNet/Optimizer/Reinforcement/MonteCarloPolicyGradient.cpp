
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "MonteCarloPolicyGradient.h"

namespace TinNet::Optimizer::Reinforcement
{
	MonteCarloPolicyGradient::MonteCarloPolicyGradient(NN &sNN, float nNewLearningRate) :
		sNN{sNN},
		nLearningRate{nNewLearningRate},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())},
		sForwardOutput(sNN.depth()),
		sBackwardOutput(sNN.depth()),
		sActivationInput(sNN.depth()),
		sActivationOutput(sNN.depth()),
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth()),
		sBiasRate(sNN.depth()),
		sWeightRate(sNN.depth())
	{
		for (std::size_t nIndex{0}, nDepth{sNN.depth()}; nIndex < nDepth; ++nIndex)
		{
			auto pLayer{this->sNN[nIndex]};

			std::size_t nActivationInputSize;
			std::size_t nActivationOutputSize;
			std::size_t nBiasDeltaSize;
			std::size_t nWeightDeltaSize;

			pLayer->specifySize(nActivationInputSize, nActivationOutputSize, nBiasDeltaSize, nWeightDeltaSize);

			this->sForwardOutput[nIndex].resize(pLayer->fanOut(), .0f);
			this->sBackwardOutput[nIndex].resize(pLayer->fanIn(), .0f);
			this->sActivationInput[nIndex].resize(pLayer->fanOut(), .0f);
			this->sActivationOutput[nIndex].resize(pLayer->fanOut(), .0f);
			this->sBiasDelta[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightDelta[nIndex].resize(nWeightDeltaSize, .0f);
			this->sBiasRate[nIndex].resize(nBiasDeltaSize, .0f);
			this->sWeightRate[nIndex].resize(nWeightDeltaSize, .0f);
		}
	}

	MonteCarloPolicyGradient::MonteCarloPolicyGradient(MonteCarloPolicyGradient &&sSrc) :
		sNN{sSrc.sNN},
		nLearningRate{sSrc.nLearningRate},
		sEngine{std::move(sSrc.sEngine)},
		sForwardOutput{std::move(sSrc.sForwardOutput)},
		sBackwardOutput{std::move(sSrc.sBackwardOutput)},
		sActivationInput{std::move(sSrc.sActivationInput)},
		sActivationOutput{std::move(sSrc.sActivationOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)},
		sBiasRate{std::move(sSrc.sBiasRate)},
		sWeightRate{std::move(sSrc.sWeightRate)}
	{
		//Empty.
	}

	void MonteCarloPolicyGradient::update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward)
	{
		//auto nDimension{pActionTaken->size()};
		//
		////Shuffle the input/output vector.
		//for (std::size_t nRand{0}, nRandSize{nSize - 1}; nRand < nRandSize; ++nRand)
		//{
		//	auto nIndex = std::uniform_int_distribution<std::size_t>{nRand + 1, nRandSize}(this->sEngine);
		//
		//	pState[nRand].swap(pState[nIndex]);
		//	pActionTaken[nRand].swap(pActionTaken[nIndex]);
		//	std::swap(pReward[nRand], pReward[nIndex]);
		//}
		//
		//for (std::size_t nIn{0}; nIn < nSize; ++nIn)
		//{
		//	//Forward pass.
		//	this->sNN.forward(pState[nIn].data(), this->sForwardOutput.data(), this->sActivationInput.data(), this->sActivationOutput.data());
		//
		//	//Give the backward input.
		//	std::copy(pActionTaken[nIn].cbegin(), pActionTaken[nIn].cend(), this->sForwardOutput.back().begin());
		//
		//	//Backward pass.
		//	this->sNN.backward(
		//		pState[nIn].data(),
		//		this->sForwardOutput.back().data(),
		//		this->sForwardOutput.data(),
		//		this->sBackwardOutput.data(),
		//		this->sActivationInput.data(),
		//		this->sActivationOutput.data(),
		//		this->sBiasDelta.data(),
		//		this->sWeightDelta.data());
		//
		//	const auto nFactor{-this->nLearningRate * pReward[nIn]};
		//
		//	for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		//	{
		//		for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasRate[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
		//			this->sBiasRate[nIndex][nBiasIndex] += this->sBiasDelta[nIndex][nBiasIndex] * this->sBiasDelta[nIndex][nBiasIndex];
		//
		//		for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightRate[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
		//			this->sWeightRate[nIndex][nWeightIndex] += this->sWeightDelta[nIndex][nWeightIndex] * this->sWeightDelta[nIndex][nWeightIndex];
		//	}
		//
		//	for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		//	{
		//		for (std::size_t nBiasIndex{0}, nBiasSize{this->sBiasDelta[nIndex].size()}; nBiasIndex < nBiasSize; ++nBiasIndex)
		//			this->sBiasDelta[nIndex][nBiasIndex] *= nFactor / std::sqrt(this->sBiasRate[nIndex][nBiasIndex] + 1e-4f);
		//
		//		for (std::size_t nWeightIndex{0}, nWeightSize{this->sWeightDelta[nIndex].size()}; nWeightIndex < nWeightSize; ++nWeightIndex)
		//			this->sWeightDelta[nIndex][nWeightIndex] *= nFactor / std::sqrt(this->sWeightRate[nIndex][nWeightIndex] + 1e-4f);
		//	}
		//
		//	for (std::size_t nIndex{0}, nDepth{this->sNN.depth()}; nIndex < nDepth; ++nIndex)
		//		this->sNN[nIndex]->update(this->sBiasDelta[nIndex].data(), this->sWeightDelta[nIndex].data());
		//}
	}
}