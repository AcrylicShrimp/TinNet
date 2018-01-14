
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Layer.h"

namespace CaysNet::Layer
{
	Layer::Layer(std::size_t nFanIn, std::size_t nFanOut) :
		nFanIn{nFanIn},
		nFanOut{nFanOut}
	{
		//Empty.
	}

	Layer::Layer(const Layer &sSrc) :
		nFanIn{sSrc.nFanIn},
		nFanOut{sSrc.nFanOut}
	{
		//Empty.
	}

	Layer &Layer::operator=(const Layer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nFanIn = sSrc.nFanIn;
		this->nFanOut = sSrc.nFanOut;

		return *this;
	}
}