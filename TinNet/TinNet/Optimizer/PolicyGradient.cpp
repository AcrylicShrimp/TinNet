
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "PolicyGradient.h"

namespace TinNet::Optimizer
{
	PolicyGradient::PolicyGradient(OptimizerBase &sPolicy) :
		sPolicy{sPolicy}
	{
		//Empty.
	}

	PolicyGradient::PolicyGradient(PolicyGradient &&sSrc) :
		sPolicy{sSrc.sPolicy}
	{
		//Empty.
	}

	void PolicyGradient::update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward)
	{
		this->sPolicy.computeGradient(nSize, pState, pActionTaken,
		[pReward, pActionTaken](std::size_t nActualBatchSize, std::vector<std::vector<float>> &sNetworkOutput, std::vector<std::vector<float>> &sBackwardInput)
		{
			for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
				Loss::MulticlassCE::derivative(pActionTaken[nIndex].size(), sNetworkOutput[nIndex].data(), pActionTaken[nIndex].data(), sBackwardInput[nIndex].data());

			return pReward;
		},
		[this](std::size_t nActualBatchSize)
		{
			this->sPolicy.applyGradient(nActualBatchSize, 1.f);
		});
	}
}