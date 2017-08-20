
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "Xavier.h"

namespace CaysNet::Initializer
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

	void Xavier::initializeBias(Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(1. / sLayer.fanIn())};

		for (auto &nBias : sLayer.bias())
			nBias = static_cast<float>(sDist(this->sEngine));
	}

	void Xavier::initializeWeight(Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(1. / sLayer.fanIn())};

		for (auto &sWeightList : sLayer.weight())
			for (auto &nWeight : sWeightList)
				nWeight = static_cast<float>(sDist(this->sEngine));
	}
}