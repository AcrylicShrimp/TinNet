
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "MSE.h"

namespace CaysNet::Loss
{
	float MSE::loss(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput)
	{
		auto nLoss{(pNetworkOutput[0] - pDesiredOutput[0]) * (pNetworkOutput[0] - pDesiredOutput[0])};

		for (std::size_t nIndex{1}; nIndex < nLength; ++nIndex)
			nLoss += (pNetworkOutput[nIndex] - pDesiredOutput[nIndex]) * (pNetworkOutput[nIndex] - pDesiredOutput[nIndex]);

		return nLoss / nLength;
	}

	void MSE::derivative(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput, float *pResult)
	{
		auto nFactor{2.f / nLength};

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = nFactor * (pNetworkOutput[nIndex] - pDesiredOutput[nIndex]);
	}
}