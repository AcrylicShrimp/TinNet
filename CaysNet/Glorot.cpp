
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "Glorot.h"

namespace CaysNet::Initializer
{
	Glorot::Glorot() :
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	Glorot::Glorot(std::mt19937_64::result_type nSeed) :
		sEngine{nSeed}
	{
		//Empty.
	}

	Glorot::Glorot(const Glorot &sSrc) :
		sEngine{sSrc.sEngine}
	{
		//Empty.
	}

	Glorot::Glorot(Glorot &&sSrc) :
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}

	Glorot &Glorot::operator=(const Glorot &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sEngine = sSrc.sEngine;

		return *this;
	}

	Glorot &Glorot::operator=(Glorot &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sEngine = std::move(sSrc.sEngine);

		return *this;
	}

	void Glorot::initializeBias(Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(2. / (sLayer.fanIn() + sLayer.fanOut()))};

		for (auto &nBias : sLayer.bias())
			nBias = static_cast<float>(sDist(this->sEngine));
	}

	void Glorot::initializeWeight(Layer &sLayer)
	{
		std::normal_distribution<double> sDist{.0, std::sqrt(2. / (sLayer.fanIn() + sLayer.fanOut()))};

		for (auto &sWeightList : sLayer.weight())
			for (auto &nWeight : sWeightList)
				nWeight = static_cast<float>(sDist(this->sEngine));
	}
}