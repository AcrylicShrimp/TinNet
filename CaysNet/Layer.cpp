
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#include "Layer.h"

#include "Activation.h"

namespace CaysNet
{
	Layer::Layer(std::size_t nFanIn, std::size_t nFanOut) :
		sWeight(nFanOut, std::vector<float>(nFanIn, .0f)),
		sBias(nFanOut, .0f),
		pActivation{nullptr}
	{
		//Empty.
	}
	
	Layer::Layer(const Layer &sSrc) :
		sWeight{sSrc.sWeight},
		sBias{sSrc.sBias},
		pActivation{sSrc.pActivation}
	{
		//Empty.
	}
	
	Layer::Layer(Layer &&sSrc) :
		sWeight{std::move(sSrc.sWeight)},
		sBias{std::move(sSrc.sBias)},
		pActivation{std::move(sSrc.pActivation)}
	{
		//Empty.
	}
	
	Layer &Layer::operator=(const Layer &sSrc)
	{
		if(&sSrc == this)
			return *this;
		
		this->sWeight = sSrc.sWeight;
		this->sBias = sSrc.sBias;
		this->pActivation = sSrc.pActivation;
		
		return *this;
	}
	
	Layer &Layer::operator=(Layer &&sSrc)
	{
		if(&sSrc == this)
			return *this;
		
		this->sWeight = sSrc.sWeight;
		this->sBias = sSrc.sBias;
		this->pActivation = sSrc.pActivation;
		
		return *this;
	}

	void Layer::calc(const float *pInput, float *pOutput) const
	{
		//z = X * W + b
		for (std::size_t nSecond = 0, nSecondSize = this->fanOut(); nSecond < nSecondSize; ++nSecond)
		{
			auto &nDestination{pOutput[nSecond] = this->sBias[nSecond]};

			for (std::size_t nFirst = 0, nFirstSize = this->fanIn(); nFirst < nFirstSize; ++nFirst)
				nDestination += pInput[nFirst] * this->sWeight[nSecond][nFirst];
		}

		//a = f(z)
		assert(this->pActivation);
		this->pActivation->activate(this, pOutput);
	}
}