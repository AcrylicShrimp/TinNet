
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "CE.h"

namespace TinNet::Loss
{
	float CE::loss(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput)
	{
		auto nLoss{-pDesiredOutput[0] * std::log(pNetworkOutput[0] + 1e-4f) + (pDesiredOutput[0] - 1.f) * std::log(1.f - pNetworkOutput[0] + 1e-4f)};

		for (std::size_t nIndex{1}; nIndex < nLength; ++nIndex)
			nLoss += -pDesiredOutput[nIndex] * std::log(pNetworkOutput[nIndex] + 1e-4f) + (pDesiredOutput[nIndex] - 1.f) * std::log(1.f - pNetworkOutput[nIndex] + 1e-4f);

		return nLoss;
	}

	void CE::derivative(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput, float *pResult)
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = (pNetworkOutput[nIndex] - pDesiredOutput[nIndex]) / (pNetworkOutput[nIndex] - pNetworkOutput[nIndex] * pNetworkOutput[nIndex] + 1e-4f);
	}
}