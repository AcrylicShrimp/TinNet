
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "Xavier.h"

namespace TinNet::Initializer
{
	Xavier::Xavier() :
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	Xavier::Xavier(std::mt19937_64::result_type nSeed) :
		sEngine{nSeed}
	{
		//Empty.
	}

	Xavier::Xavier(const Xavier &sSrc) :
		sEngine{sSrc.sEngine}
	{
		//Empty.
	}

	Xavier::Xavier(Xavier &&sSrc) :
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}

	Xavier &Xavier::operator=(const Xavier &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sEngine = sSrc.sEngine;

		return *this;
	}

	Xavier &Xavier::operator=(Xavier &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sEngine = std::move(sSrc.sEngine);

		return *this;
	}

	void Xavier::initializeBias(Layer::Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(1. / sLayer.fanIn())};

		sLayer.initBias([this, &sDist]()
		{
			return static_cast<float>(sDist(this->sEngine));
		});
	}

	void Xavier::initializeWeight(Layer::Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(1. / sLayer.fanIn())};

		sLayer.initWeight([this, &sDist]()
		{
			return static_cast<float>(sDist(this->sEngine));
		});
	}
}