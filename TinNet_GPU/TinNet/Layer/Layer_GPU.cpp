
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "Layer_GPU.h"

namespace TinNet::Layer
{
	Layer_GPU::Layer_GPU(std::size_t nFanIn, std::size_t nFanOut) :
		nFanIn{nFanIn},
		nFanOut{nFanOut}
	{
		//Empty.
	}
	
	Layer_GPU::Layer_GPU(const Layer_GPU &sSrc) :
		nFanIn{sSrc.nFanIn},
		nFanOut{sSrc.nFanOut}
	{
		//Empty.
	}

	Layer_GPU &Layer_GPU::operator=(const Layer_GPU &sSrc)
	{
		if (&sSrc == this)
			return *this;
		
		this->nFanIn = sSrc.nFanIn;
		this->nFanOut = sSrc.nFanOut;
		
		return *this;
	}

	std::size_t Layer_GPU::fanIn() const
	{
		return this->nFanIn;
	}

	std::size_t Layer_GPU::fanOut() const
	{
		return this->nFanOut;
	}
}