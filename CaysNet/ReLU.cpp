
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "ReLU.h"

namespace CaysNet::Activation
{
	void ReLU::activate(const Layer *pLayer, float *pOutput) const
	{
		static const float vDesk[2]{.0f, 1.f};

		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] = vDesk[pOutput[nIndex] > .0f] * pOutput[nIndex];
	}

	void ReLU::derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const
	{
		static const float vDesk[2]{.0f, 1.f};

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = vDesk[pInput[nIndex] > .0f];
	}

	Activation *ReLU::duplicate() const
	{
		return new ReLU();
	}
}