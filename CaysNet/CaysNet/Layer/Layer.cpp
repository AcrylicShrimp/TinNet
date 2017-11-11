
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Layer.h"

namespace CaysNet::Layer
{
	Layer::Layer(Activation::Activation *pNewActivation, std::size_t nFanIn, std::size_t nFanOut) :
		pActivation{pNewActivation},
		nFanIn{nFanIn},
		nFanOut{nFanOut}
	{
		//Empty.
	}

	Layer::Layer(const Layer &sSrc) :
		pActivation{sSrc.pActivation->duplicate()},
		nFanIn{sSrc.nFanIn},
		nFanOut{sSrc.nFanOut}
	{
		//Empty.
	}

	Layer::Layer(Layer &&sSrc) :
		pActivation{sSrc.pActivation},
		nFanIn{sSrc.nFanIn},
		nFanOut{sSrc.nFanOut}
	{
		sSrc.pActivation = nullptr;
		sSrc.nFanIn = sSrc.nFanOut = 0;
	}

	Layer::~Layer()
	{
		if (!this->pActivation)
			return;

		delete this->pActivation;
		this->pActivation = nullptr;
	}

	Layer &Layer::operator=(const Layer &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Layer();
		this->pActivation = sSrc.pActivation->duplicate();
		this->nFanIn = sSrc.nFanIn;
		this->nFanOut = sSrc.nFanOut;

		return *this;
	}

	Layer &Layer::operator=(Layer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Layer();
		this->pActivation = sSrc.pActivation;
		this->nFanIn = sSrc.nFanIn;
		this->nFanOut = sSrc.nFanOut;

		sSrc.pActivation = nullptr;
		sSrc.nFanIn = sSrc.nFanOut = 0;

		return *this;
	}

	void Layer::serialize(std::ofstream &sOutput) const
	{
		Activation::Activations::serialize(this->pActivation, sOutput);
	}

	void Layer::deserialize(std::ifstream &sInput)
	{
		this->~Layer();
		this->pActivation = Activation::Activations::deserialize(sInput);
	}
}