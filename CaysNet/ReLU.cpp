
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

		for (std::size_t nIndex = 0, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
			pOutput[nIndex] = vDesk[pOutput[nIndex] > .0f] * pOutput[nIndex];
	}

	float ReLU::derivative(float nZ, float nY) const
	{
		static const float vDesk[2]{.0f, 1.f};

		return vDesk[nZ > .0f];
	}

	Activation *ReLU::duplicate() const
	{
		return new ReLU();
	}
}