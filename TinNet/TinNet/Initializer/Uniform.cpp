
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "Uniform.h"

namespace TinNet::Initializer
{
	Uniform::Uniform(double nNewMin, double nNewMax) :
		nMin{nNewMin},
		nMax{nNewMax},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		if (this->nMin > this->nMax)
		{
			auto nTemp = this->nMin;
			this->nMin = this->nMax;
			this->nMax = nTemp;
		}
	}

	Uniform::Uniform(std::mt19937_64::result_type nSeed, double nNewMin, double nNewMax) :
		nMin{nNewMin},
		nMax{nNewMax},
		sEngine{nSeed}
	{
		if (this->nMin > this->nMax)
		{
			auto nTemp = this->nMin;
			this->nMin = this->nMax;
			this->nMax = nTemp;
		}
	}

	Uniform::Uniform(const Uniform &sSrc) :
		nMin{sSrc.nMin},
		nMax{sSrc.nMax},
		sEngine{sSrc.sEngine}
	{
		//Empty.
	}

	Uniform::Uniform(Uniform &&sSrc) :
		nMin{sSrc.nMin},
		nMax{sSrc.nMax},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}

	Uniform &Uniform::operator=(const Uniform &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nMin = sSrc.nMin;
		this->nMax = sSrc.nMax;
		this->sEngine = sSrc.sEngine;

		return *this;
	}

	Uniform &Uniform::operator=(Uniform &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nMin = sSrc.nMin;
		this->nMax = sSrc.nMax;
		this->sEngine = std::move(sSrc.sEngine);

		return *this;
	}

	void Uniform::initializeBias(Layer::Layer &sLayer)
	{
		std::uniform_real_distribution<double> sDist{this->nMin, this->nMax};

		sLayer.initBias([this, &sDist]()
		{
			return static_cast<float>(sDist(this->sEngine));
		});
	}

	void Uniform::initializeWeight(Layer::Layer &sLayer)
	{
		std::uniform_real_distribution<double> sDist{this->nMin, this->nMax};

		sLayer.initWeight([this, &sDist]()
		{
			return static_cast<float>(sDist(this->sEngine));
		});
	}
}