
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Linear.h"

namespace CaysNet::Activation
{
	Activation *Linear::duplicate() const
	{
		return new Linear();
	}

	void Linear::activate(const Layer *pLayer, float *pOutput) const
	{
		//Empty.
	}

	void Linear::derivative(
		std::size_t nLength,
		const float *pActivationInput,
		const float *pActivationOutput,
		const float *pDerivativeInput,
		float *pResult) const
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = pDerivativeInput[nIndex];
	}
}