
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "TanH.h"

namespace CaysNet::Activation
{
	void TanH::activate(const Layer *pLayer, float *pOutput) const
	{
		for (std::size_t nIndex = 0, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
			pOutput[nIndex] = std::tanh(pOutput[nIndex]);
	}

	float TanH::derivative(float nZ, float nY) const
	{
		return 1.f - nY * nY;
	}

	Activation *TanH::duplicate() const
	{
		return new TanH();
	}
}