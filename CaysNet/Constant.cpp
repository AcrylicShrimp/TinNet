
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "Constant.h"

namespace CaysNet::Initializer
{
	Constant::Constant(float nNewConstant) :
		nConstant{nNewConstant}
	{
		//Empty.
	}

	Constant::Constant(const Constant &sSrc) :
		nConstant{sSrc.nConstant}
	{
		//Empty.
	}

	Constant &Constant::operator=(const Constant &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nConstant = sSrc.nConstant;

		return *this;
	}

	void Constant::initializeBias(Layer &sLayer) const
	{
		for (auto &nBias : sLayer.bias())
			nBias = this->nConstant;
	}

	void Constant::initializeWeight(Layer &sLayer) const
	{
		for (auto &sWeightList : sLayer.weight())
			for (auto &nWeight : sWeightList)
				nWeight = this->nConstant;
	}
}