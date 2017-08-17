
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "ReLU.h"

namespace CaysNet::Activation
{
	const wchar_t *ReLU::name() const
	{
		return L"ReLU";
	}

	Activation *ReLU::duplicate() const
	{
		return new ReLU();
	}

	void ReLU::activate(const Layer *pLayer, float *pOutput) const
	{
		static constexpr float vDesk[2]{.0f, 1.f};

		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] = vDesk[pOutput[nIndex] > .0f] * pOutput[nIndex];
	}

	void ReLU::derivative(
		std::size_t nLength,
		const float *pActivationInput,
		const float *pActivationOutput,
		const float *pDerivativeInput,
		float *pResult) const
	{
		static constexpr float vDesk[2]{.0f, 1.f};

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = pDerivativeInput[nIndex] * vDesk[pActivationInput[nIndex] > .0f];
	}
}