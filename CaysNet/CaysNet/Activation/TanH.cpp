
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "TanH.h"

namespace CaysNet::Activation
{
	const wchar_t *TanH::name() const
	{
		return L"TanH";
	}

	Activation *TanH::duplicate() const
	{
		return new TanH();
	}

	void TanH::activate(const Layer *pLayer, float *pOutput) const
	{
		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] = std::tanh(pOutput[nIndex]);
	}

	void TanH::derivative(
		std::size_t nLength,
		const float *pActivationInput,
		const float *pActivationOutput,
		const float *pDerivativeInput,
		float *pResult) const
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = pDerivativeInput[nIndex] * (1.f - pActivationOutput[nIndex] * pActivationOutput[nIndex]);
	}
}