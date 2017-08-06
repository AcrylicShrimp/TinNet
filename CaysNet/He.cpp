
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "He.h"

namespace CaysNet::Initializer
{
	He::He() :
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	He::He(std::mt19937_64::result_type nSeed) :
		sEngine{nSeed}
	{
		//Empty.
	}

	He::He(const He &sSrc) :
		sEngine{sSrc.sEngine}
	{
		//Empty.
	}

	He::He(He &&sSrc) :
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}

	He &He::operator=(const He &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sEngine = sSrc.sEngine;

		return *this;
	}

	He &He::operator=(He &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sEngine = std::move(sSrc.sEngine);

		return *this;
	}

	void He::initializeBias(Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(2. / sLayer.fanIn())};

		for (auto &nBias : sLayer.bias())
			nBias = static_cast<float>(sDist(this->sEngine));
	}

	void He::initializeWeight(Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(2. / sLayer.fanIn())};

		for (auto &sWeightList : sLayer.weight())
			for (auto &nWeight : sWeightList)
				nWeight = static_cast<float>(sDist(this->sEngine));
	}
}