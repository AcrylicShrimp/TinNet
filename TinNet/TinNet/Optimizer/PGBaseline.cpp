
/*
	2018.03.24
	Created by AcrylicShrimp.
*/

#include "PGBaseline.h"

namespace TinNet::Optimizer
{
	PGBaseline::PGBaseline(OptimizerBase &sValue, OptimizerBase &sPolicy) :
		sValue{sValue},
		sPolicy{sPolicy}
	{
		//Empty.
	}

	PGBaseline::PGBaseline(PGBaseline &&sSrc) :
		sValue{sSrc.sValue},
		sPolicy{sSrc.sPolicy}
	{
		//Empty.
	}

	void PGBaseline::update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward)
	{
		std::vector<std::vector<float>> sReward(nSize);

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex)
			sReward[nIndex].resize(1, pReward[nIndex]);

		this->sPolicy.computeGradient(nSize, pState, pActionTaken,
		[this, pState, pReward, pActionTaken](std::size_t nActualBatchSize, std::vector<std::vector<float>> &sNetworkOutput, std::vector<std::vector<float>> &sBackwardInput)
		{
			for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
				Loss::MulticlassCE::derivative(pActionTaken[nIndex].size(), sNetworkOutput[nIndex].data(), pActionTaken[nIndex].data(), sBackwardInput[nIndex].data());

			for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
			{
				float nBaseline;
				this->sValue.network().forward(pState[nIndex].data(), &nBaseline);

				pReward[nIndex] -= nBaseline;
			}

			return pReward;
		},
		[this](std::size_t nActualBatchSize)
		{
			this->sPolicy.applyGradient(nActualBatchSize, 1.f);
		});

		this->sValue.train<Loss::MSE>(1, nSize, pState, sReward.data());
	}
}