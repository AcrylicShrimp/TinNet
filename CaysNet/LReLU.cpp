
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "LReLU.h"

namespace CaysNet::Activation
{
	void LReLU::activate(const Layer *pLayer, float *pOutput) const
	{
		static const float vDesk[2]{.01f, 1.f};

		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] = vDesk[pOutput[nIndex] > .0f] * pOutput[nIndex];
	}

	void LReLU::derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const
	{
		static const float vDesk[2]{.01f, 1.f};

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = vDesk[pInput[nIndex] > .0f];
	}

	Activation *LReLU::duplicate() const
	{
		return new LReLU();
	}
}