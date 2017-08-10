
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "TanH.h"

namespace CaysNet::Activation
{
	void TanH::activate(const Layer *pLayer, float *pOutput) const
	{
		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] = std::tanh(pOutput[nIndex]);
	}

	void TanH::derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = 1.f - pOutput[nIndex] * pOutput[nIndex];
	}

	Activation *TanH::duplicate() const
	{
		return new TanH();
	}
}