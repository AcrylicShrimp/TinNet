
/*
	2018.01.14
	Created by AcrylicShrimp.
*/

#include "OptimizerHelper.h"

namespace CaysNet::Optimizer
{
	void OptimizerHelper::shuffleTrainingSet(std::size_t nSize, std::vector<float> *pInput, std::vector<float> *pOutput)
	{
		std::mt19937_64 sEngine{static_cast<decltype(sEngine)::result_type>(std::chrono::system_clock::now().time_since_epoch().count())};

		for (std::size_t nRand{0}, nRandSize{nSize - 1}; nRand < nRandSize; ++nRand)
		{
			auto nIndex{std::uniform_int_distribution<std::size_t>{nRand + 1, nRandSize}(sEngine)};

			pInput[nRand].swap(pInput[nIndex]);
			pOutput[nRand].swap(pOutput[nIndex]);
		}
	}

	void OptimizerHelper::zeros(std::vector<float> &sDst)
	{
		std::fill(sDst.begin(), sDst.end(), .0f);
	}

	void OptimizerHelper::zeros(std::vector<std::vector<float>> &sDst)
	{
		for (auto &sDst : sDst)
			std::fill(sDst.begin(), sDst.end(), .0f);
	}

	void OptimizerHelper::zeros(std::vector<std::vector<std::vector<float>>> &sDst)
	{
		for (auto &sDst : sDst)
			for (auto &sDst : sDst)
				std::fill(sDst.begin(), sDst.end(), .0f);
	}
}