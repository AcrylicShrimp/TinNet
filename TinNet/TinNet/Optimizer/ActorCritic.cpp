
/*
	2018.03.25
	Created by AcrylicShrimp.
*/

#include "ActorCritic.h"

namespace TinNet::Optimizer
{
	ActorCritic::ActorCritic(OptimizerBase &sValue, OptimizerBase &sPolicy) :
		sValue{sValue},
		sPolicy{sPolicy}
	{
		//Empty.
	}

	ActorCritic::ActorCritic(ActorCritic &&sSrc) :
		sValue{sSrc.sValue},
		sPolicy{sSrc.sPolicy}
	{
		//Empty.
	}

	void ActorCritic::update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward, float nDiscountFactor)
	{
		std::vector<std::vector<float>> sReward(nSize - 1);

		this->sPolicy.computeGradient(nSize - 1, pState, pActionTaken,
		[this, pState, pReward, pActionTaken, nDiscountFactor, &sReward](std::size_t nActualBatchSize, std::vector<std::vector<float>> &sNetworkOutput, std::vector<std::vector<float>> &sBackwardInput)
		{
			for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
				Loss::MulticlassCE::derivative(pActionTaken[nIndex].size(), sNetworkOutput[nIndex].data(), pActionTaken[nIndex].data(), sBackwardInput[nIndex].data());

			for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
			{
				float nNextValue;
				float nCurrentValue;
				this->sValue.network().forward(pState[nIndex + 1].data(), &nNextValue);
				this->sValue.network().forward(pState[nIndex].data(), &nCurrentValue);

				sReward[nIndex].resize(1, pReward[nIndex] + nDiscountFactor * nNextValue);
				pReward[nIndex] = sReward[nIndex].front() - nCurrentValue;
			}

			return pReward;
		},
		[this](std::size_t nActualBatchSize)
		{
			this->sPolicy.applyGradient(nActualBatchSize, 1.f);
		});

		this->sValue.train<Loss::MSE>(1, nSize - 1, pState, sReward.data());
	}
}