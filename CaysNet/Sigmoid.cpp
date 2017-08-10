
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Sigmoid.h"

namespace CaysNet::Activation
{
	void Sigmoid::activate(const Layer *pLayer, float *pOutput) const
	{
		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] = 1.f / (std::exp(-pOutput[nIndex]) + 1.f);
	}

	void Sigmoid::derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = pOutput[nIndex] * (1.f - pOutput[nIndex]);
	}

	Activation *Sigmoid::duplicate() const
	{
		return new Sigmoid();
	}
}