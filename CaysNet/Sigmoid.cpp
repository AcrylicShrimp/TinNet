
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Sigmoid.h"

namespace CaysNet::Activation
{
	void Sigmoid::activate(const Layer *pLayer, float *pOutput) const
	{
		for (std::size_t nIndex = 0, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
			pOutput[nIndex] = 1.f / (std::exp(-pOutput[nIndex]) + 1.f);
	}

	float Sigmoid::derivative(float nZ, float nY) const
	{
		return nY * (1.f - nY);
	}

	Activation *Sigmoid::duplicate() const
	{
		return new Sigmoid();
	}
}