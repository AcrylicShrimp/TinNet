
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Sigmoid.h"

namespace CaysNet::Activation
{
	Activation *Sigmoid::duplicate() const
	{
		return new Sigmoid();
	}

	void Sigmoid::activate(const Layer *pLayer, float *pOutput) const
	{
		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] = 1.f / (std::exp(-pOutput[nIndex]) + 1.f);
	}

	void Sigmoid::derivative(
		std::size_t nLength,
		const float *pActivationInput,
		const float *pActivationOutput,
		const float *pDerivativeInput,
		float *pResult) const
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = pDerivativeInput[nIndex] * pActivationOutput[nIndex] * (1.f - pActivationOutput[nIndex]);
	}
}