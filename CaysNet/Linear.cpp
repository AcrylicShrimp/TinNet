
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Linear.h"

namespace CaysNet::Activation
{
	void Linear::activate(const Layer *pLayer, float *pOutput) const
	{
		//Empty.
	}

	void Linear::derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = 1.f;
	}

	Activation *Linear::duplicate() const
	{
		return new Linear();
	}
}