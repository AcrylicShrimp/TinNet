
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "LReLU.h"

namespace CaysNet::Activation
{
	const wchar_t *LReLU::name() const
	{
		return L"LReLU";
	}

	Activation *LReLU::duplicate() const
	{
		return new LReLU();
	}

	void LReLU::activate(std::size_t nFanOut, float *pOutput) const
	{
		static constexpr float vDesk[2]{.01f, 1.f};

		for (std::size_t nIndex{0}; nIndex < nFanOut; ++nIndex)
			pOutput[nIndex] = vDesk[pOutput[nIndex] > .0f] * pOutput[nIndex];
	}

	void LReLU::derivative(
		std::size_t nLength,
		const float *pActivationInput,
		const float *pActivationOutput,
		const float *pDerivativeInput,
		float *pResult) const
	{
		static constexpr float vDesk[2]{.01f, 1.f};

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = pDerivativeInput[nIndex] * vDesk[pActivationInput[nIndex] > .0f];
	}
}