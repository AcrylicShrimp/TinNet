
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "MonteCarloPolicyGradient.h"

namespace TinNet::Optimizer
{
	MonteCarloPolicyGradient::MonteCarloPolicyGradient(OptimizerBase &sOptimizerBase) :
		sOptimizerBase{sOptimizerBase},
		sBackwardInput(sOptimizerBase.network().layer().back()->fanOut(), .0f),
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	MonteCarloPolicyGradient::MonteCarloPolicyGradient(MonteCarloPolicyGradient &&sSrc) :
		sOptimizerBase{sSrc.sOptimizerBase},
		sBackwardInput{sSrc.sBackwardInput},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}

	void MonteCarloPolicyGradient::update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward)
	{
		this->sOptimizerBase.computeGradient(nSize, pState, pActionTaken,
		[pReward, pActionTaken](std::size_t nActualBatchSize, std::vector<std::vector<float>> &sNetworkOutput, std::vector<std::vector<float>> &sBackwardInput)
		{
			for (std::size_t nIndex{0}; nIndex < nActualBatchSize; ++nIndex)
				Loss::MulticlassCE::derivative(pActionTaken[nIndex].size(), sNetworkOutput[nIndex].data(), pActionTaken[nIndex].data(), sBackwardInput[nIndex].data());

			return pReward;
		},
		[this](std::size_t nActualBatchSize)
		{
			this->sOptimizerBase.applyGradient(nActualBatchSize, 1.f);
		});
	}
}