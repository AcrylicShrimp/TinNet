
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "MulticlassCE.h"

namespace CaysNet::Loss
{
	float MulticlassCE::loss(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput)
	{
		auto nLoss{-pDesiredOutput[0] * std::log(pNetworkOutput[0])};

		for (std::size_t nIndex{1}; nIndex < nLength; ++nIndex)
			nLoss += -pDesiredOutput[nIndex] * std::log(pNetworkOutput[nIndex]);

		return nLoss;
	}

	void MulticlassCE::derivative(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput, float *pResult)
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = -pDesiredOutput[nIndex] / pNetworkOutput[nIndex];
	}
}