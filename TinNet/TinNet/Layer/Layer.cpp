
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Layer.h"

namespace TinNet::Layer
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

	std::size_t Layer::fanIn() const
	{
		return this->nFanIn;
	}

	std::size_t Layer::fanOut() const
	{
		return this->nFanOut;
	}

	void Layer::serialize(std::ofstream &sOutput) const
	{
		IO::Serializable::write(sOutput, this->nFanIn);
		IO::Serializable::write(sOutput, this->nFanOut);
	}

	void Layer::deserialize(std::ifstream &sInput)
	{
		this->nFanIn = IO::Serializable::read<decltype(this->nFanIn)>(sInput);
		this->nFanOut = IO::Serializable::read<decltype(this->nFanOut)>(sInput);
	}
}