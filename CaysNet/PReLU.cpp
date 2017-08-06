
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "PReLU.h"

namespace CaysNet::Activation
{
	PReLU::PReLU(float nNewFactor) :
		nFactor{nNewFactor}
	{
		//Empty.
	}

	PReLU::PReLU(const PReLU &sSrc) :
		nFactor{sSrc.nFactor}
	{
		//Empty.
	}

	PReLU &PReLU::operator=(const PReLU &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nFactor = sSrc.nFactor;

		return *this;
	}

	PReLU &PReLU::operator=(float nNewFactor)
	{
		this->nFactor = nNewFactor;

		return *this;
	}

	void PReLU::activate(const Layer *pLayer, float *pOutput) const
	{
		float vDesk[2]{this->nFactor, 1.f};

		for (std::size_t nIndex = 0, nSize = pLayer->fanOut(); nIndex < nSize; ++nIndex)
			pOutput[nIndex] = vDesk[pOutput[nIndex] > .0f] * pOutput[nIndex];
	}

	float PReLU::derivative(float nZ, float nY) const
	{
		float vDesk[2]{this->nFactor, 1.f};

		return vDesk[nZ > .0f];
	}

	Activation *PReLU::duplicate() const
	{
		return new PReLU(this->nFactor);
	}
}