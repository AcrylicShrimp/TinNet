
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Softmax.h"

namespace CaysNet::Activation
{
	const wchar_t *Softmax::name() const
	{
		return L"Softmax";
	}

	Activation *Softmax::duplicate() const
	{
		return new Softmax();
	}

	void Softmax::activate(const Layer *pLayer, float *pOutput) const
	{
		//Desk[0] : Max output
		//Desk[1] : Accumulator
		float vDesk[2]{pOutput[0], pOutput[0]};

		//Find max value.
		for (std::size_t nIndex{1}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
		{
			vDesk[1] = pOutput[nIndex];
			vDesk[0] = vDesk[vDesk[1] > vDesk[0]];
		}

		//Clear the accumulator.
		vDesk[1] = .0f;

		//Accumulate and fill.
		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			vDesk[1] += (pOutput[nIndex] = std::exp(pOutput[nIndex] - vDesk[0]));

		//UNDER TEST
		if (vDesk[1] == .0f)
			return;

		//Divide by the accumulated value.
		for (std::size_t nIndex{0}, nSize{pLayer->fanOut()}; nIndex < nSize; ++nIndex)
			pOutput[nIndex] /= vDesk[1];
	}

	void Softmax::derivative(
		std::size_t nLength,
		const float *pActivationInput,
		const float *pActivationOutput,
		const float *pDerivativeInput,
		float *pResult) const
	{
		std::vector<float> sResult(nLength, .0f);

		for (std::size_t nFirst{0}; nFirst < nLength; ++nFirst)
			for (std::size_t nSecond{0}; nSecond < nLength; ++nSecond)
				sResult[nFirst] += pDerivativeInput[nSecond] * (nSecond == nFirst ? pActivationOutput[nSecond] * (1.f - pActivationOutput[nSecond]) : -pActivationOutput[nSecond] * pActivationOutput[nFirst]);

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			pResult[nIndex] = sResult[nIndex];
	}
}