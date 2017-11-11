
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "MonteCarloPolicyGradient.h"

namespace CaysNet::Optimizer::Reinforcement
{
	MonteCarloPolicyGradient::MonteCarloPolicyGradient(NN &sNN, float nNewLearningRate) :
		nLearningRate{nNewLearningRate},
		sNN{sNN},
		sOutput(sNN.depth()),
		sBiasDelta(sNN.depth()),
		sWeightDelta(sNN.depth())
	{
		for (std::size_t nIndex{0}, nSize{sNN.depth()}; nIndex < nSize; ++nIndex)
		{
			auto pLayer{this->sNN[nIndex]};

			this->sOutput[nIndex].resize(pLayer->fanIn(), .0f);
			this->sBiasDelta[nIndex].resize(pLayer->fanOut(), .0f);
			this->sWeightDelta[nIndex].resize(pLayer->fanOut());

			for (std::size_t nOut{0}, nOutSize{pLayer->fanOut()}, nInSize{pLayer->fanIn()}; nOut < nOutSize; ++nOut)
				this->sWeightDelta[nIndex][nOut].resize(nInSize, .0f);
		}
	}

	MonteCarloPolicyGradient::MonteCarloPolicyGradient(MonteCarloPolicyGradient &&sSrc) :
		nLearningRate{sSrc.nLearningRate},
		sNN{sSrc.sNN},
		sOutput{std::move(sSrc.sOutput)},
		sBiasDelta{std::move(sSrc.sBiasDelta)},
		sWeightDelta{std::move(sSrc.sWeightDelta)}
	{
		//Empty.
	}

	//double CaysNet::Optimizer::Reinforcement::MonteCarloPolicyGradient::checkGradient(const float *pState, const float *pActionTaken, float nReward, std::size_t nLayerIndex, std::size_t nInputIndex, std::size_t nOutputIndex)
	//{
	//	constexpr auto nEpsilon{1e-3f};
	//
	//	float nWeight{this->sNN[nLayerIndex]->weight()[nOutputIndex][nInputIndex]};
	//
	//	this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight + nEpsilon;
	//	this->sNN.calc(pState);
	//
	//	const auto *pAction{pActionTaken};
	//	float nFirst{.0f};
	//
	//	for (auto &nOutput : this->sNN.output().back())
	//		nFirst += -std::log(nOutput + 1e-4f) * *pAction++ * nReward;
	//
	//	this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight - nEpsilon;
	//	float nSecond{this->sNN.loss<Loss::MulticlassCE>(pState, pActionTaken)};
	//
	//	float nFirstGradient{(nFirst - nSecond) / (2.f * nEpsilon)};
	//
	//	this->sNN[nLayerIndex].weight()[nOutputIndex][nInputIndex] = nWeight;
	//
	//	//Forward pass.
	//	this->sNN.calcForTrain(pState);
	//
	//	//Give the backward input - derivative of the loss function.
	//	Loss::MulticlassCE::derivative(sOutput.size(), this->sNN.output().back().data(), pActionTaken, this->sNN.output().back().data());
	//
	//	//Backward pass; accrue the gradients.
	//	for (std::size_t nIndex{this->sNN.depth() - 1}; ; --nIndex)
	//	{
	//		auto &sLayer{this->sNN[nIndex]};
	//		auto pLayerInput{nIndex == 0 ? pState : this->sNN.output()[nIndex - 1].data()};
	//		auto pLayerBackInput{nIndex + 1 == this->sNN.depth() ? this->sNN.output().back().data() : this->sOutput[nIndex + 1].data()};
	//		auto pLayerBackOutput{this->sOutput[nIndex].data()};
	//
	//		pLayer->backward(pLayerBackInput, pLayerBackOutput);
	//
	//		for (std::size_t nOut{0}, nOutSize{pLayer->fanOut()}; nOut < nOutSize; ++nOut)
	//		{
	//			this->sBiasDelta[nIndex][nOut] = pLayerBackInput[nOut];
	//
	//			for (std::size_t nIn{0}, nInSize{pLayer->fanIn()}; nIn < nInSize; ++nIn)
	//				this->sWeightDelta[nIndex][nOut][nIn] = pLayerInput[nIn] * pLayerBackInput[nOut];
	//		}
	//
	//		if (nIndex == 0)
	//			break;
	//	}
	//
	//	float nSecondGradient{this->sWeightDelta[nLayerIndex][nOutputIndex][nInputIndex]};
	//
	//	if (nFirstGradient == nSecondGradient)
	//		return .0;
	//
	//	return std::abs(nFirstGradient - nSecondGradient) / std::max(std::abs(nFirstGradient), std::abs(nSecondGradient));
	//}

	void MonteCarloPolicyGradient::update(const float *pState, const float *pActionTaken, std::size_t nActionTakenIndex, float nReward)
	{
		this->sNN.forward(pState);

		auto nExpectation{-nReward * std::log(this->sNN.output().back()[nActionTakenIndex] + 1e-4f)};

		for (auto &nOutput : this->sNN.output().back())
		{
			nOutput = nExpectation;
			//++pActionTaken;
		}

		//Loss::MSE::derivative(this->sNN.output().back().size(), this->sNN.output().back().data(), pActionTaken, this->sNN.output().back().data());

		//for (auto &nOutput : this->sNN.output().back())
		//{
		//	nOutput *= nReward;
		//	//++pActionTaken;
		//}

		for (std::size_t nIndex{this->sNN.depth() - 1}; ; --nIndex)
		{
			auto pLayer{this->sNN[nIndex]};
			auto pLayerInput{nIndex == 0 ? pState : this->sNN.output()[nIndex - 1].data()};
			auto pLayerBackInput{nIndex + 1 == this->sNN.depth() ? this->sNN.output().back().data() : this->sOutput[nIndex + 1].data()};
			auto pLayerBackOutput{this->sOutput[nIndex].data()};

			//pLayer->backward(pLayerBackInput, pLayerBackOutput);

			for (std::size_t nOut{0}, nOutSize{pLayer->fanOut()}; nOut < nOutSize; ++nOut)
			{
				this->sBiasDelta[nIndex][nOut] = pLayerBackInput[nOut];

				for (std::size_t nIn{0}, nInSize{pLayer->fanIn()}; nIn < nInSize; ++nIn)
					this->sWeightDelta[nIndex][nOut][nIn] = pLayerInput[nIn] * pLayerBackInput[nOut];
			}

			if (nIndex == 0)
				break;
		}

		auto nFactor{this->nLearningRate};

		//for (std::size_t nIndex{0}, nSize{this->sNN.depth()}; nIndex < nSize; ++nIndex)
		//	for (std::size_t nOut{0}, nOutSize{this->sNN[nIndex]->fanOut()}; nOut < nOutSize; ++nOut)
		//	{
		//		this->sNN[nIndex]->bias()[nOut] += nFactor * this->sBiasDelta[nIndex][nOut];
		//
		//		for (std::size_t nIn{0}, nInSize{this->sNN[nIndex]->fanIn()}; nIn < nInSize; ++nIn)
		//			this->sNN[nIndex]->weight()[nOut][nIn] += nFactor * this->sWeightDelta[nIndex][nOut][nIn];
		//	}
	}
}