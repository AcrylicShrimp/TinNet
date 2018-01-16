
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "Constant.h"

namespace TinNet::Initializer
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

	void Constant::initializeBias(Layer::Layer &sLayer) const
	{
		sLayer.initBias([this]()
		{
			return this->nConstant;
		});
	}

	void Constant::initializeWeight(Layer::Layer &sLayer) const
	{
		sLayer.initWeight([this]()
		{
			return this->nConstant;
		});
	}
}