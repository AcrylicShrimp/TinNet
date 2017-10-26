
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
			auto &sLayer{this->sNN[nIndex]};

			this->sOutput[nIndex].resize(sLayer.fanIn(), .0f);
			this->sBiasDelta[nIndex].resize(sLayer.fanOut(), .0f);
			this->sWeightDelta[nIndex].resize(sLayer.fanOut());

			for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}, nInSize{sLayer.fanIn()}; nOut < nOutSize; ++nOut)
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

	void MonteCarloPolicyGradient::update(const float *pState, const float *pActionTaken, float nReward)
	{
		this->sNN.calcForTrain(pState);
		
		for (auto &nInput : this->sNN.output().back())
			nInput = nReward * -std::log(nInput + 1e-4f);

		for (std::size_t nIndex{this->sNN.depth() - 1}; ; --nIndex)
		{
			auto &sLayer{this->sNN[nIndex]};
			auto pLayerInput{nIndex == 0 ? pState : this->sNN.output()[nIndex - 1].data()};
			auto pLayerBackInput{nIndex + 1 == this->sNN.depth() ? this->sNN.output().back().data() : this->sOutput[nIndex + 1].data()};
			auto pLayerBackOutput{this->sOutput[nIndex].data()};

			sLayer.backward(pLayerBackInput, pLayerBackOutput);

			for (std::size_t nOut{0}, nOutSize{sLayer.fanOut()}; nOut < nOutSize; ++nOut)
			{
				this->sBiasDelta[nIndex][nOut] = pLayerBackInput[nOut];

				for (std::size_t nIn{0}, nInSize{sLayer.fanIn()}; nIn < nInSize; ++nIn)
					this->sWeightDelta[nIndex][nOut][nIn] = pLayerInput[nIn] * pLayerBackInput[nOut];
			}

			if (nIndex == 0)
				break;
		}

		auto nFactor{this->nLearningRate};

		for (std::size_t nIndex{0}, nSize{this->sNN.depth()}; nIndex < nSize; ++nIndex)
			for (std::size_t nOut{0}, nOutSize{this->sNN[nIndex].fanOut()}; nOut < nOutSize; ++nOut)
			{
				this->sNN[nIndex].bias()[nOut] += nFactor * this->sBiasDelta[nIndex][nOut];

				for (std::size_t nIn{0}, nInSize{this->sNN[nIndex].fanIn()}; nIn < nInSize; ++nIn)
					this->sNN[nIndex].weight()[nOut][nIn] += nFactor * this->sWeightDelta[nIndex][nOut][nIn];
			}
	}
}