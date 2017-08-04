
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "LReLU.h"

namespace CaysNet::Activation
{
	void LReLU::activate(const Layer *pLayer, float *pOutput) const
	{
		static float vDesk[2]{ .01f, 1.f };

		for (std::size_t nIndex = 0, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
			pOutput[nIndex] = vDesk[pOutput[nIndex] > .0f] * pOutput[nIndex];
	}

	float LReLU::derivative(float nZ) const
	{
		static float vDesk[2]{ .01f, 1.f };

		return vDesk[nZ > .0f];
	}
}