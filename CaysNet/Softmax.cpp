
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Softmax.h"

namespace CaysNet::Activation
{
	void Softmax::activate(const Layer *pLayer, float *pOutput) const
	{
		//Desk[0] : Max output
		//Desk[1] : Accumulator
		float vDesk[2]{pOutput[0], pOutput[0]};

		//Find max value.
		for (std::size_t nIndex = 1, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
		{
			vDesk[1] = pOutput[nIndex];
			vDesk[0] = vDesk[vDesk[1] > vDesk[0]];
		}

		//Clear the accumulator.
		vDesk[1] = .0f;

		//Accumulate and fill.
		for (std::size_t nIndex = 0, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
			vDesk[1] += (pOutput[nIndex] = std::exp(pOutput[nIndex] - vDesk[0]));

		//Divide by the accumulated value.
		for (std::size_t nIndex = 0, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
			pOutput[nIndex] /= (vDesk[1] + 1e-4f);
	}

	float Softmax::derivative(float nZ, float nY) const
	{
		return nY * (1.f - nY);
	}

	Activation *Softmax::duplicate() const
	{
		return new Softmax();
	}
}