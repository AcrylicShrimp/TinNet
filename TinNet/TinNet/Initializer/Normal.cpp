
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "Normal.h"

namespace TinNet::Initializer
{
	Normal::Normal() :
		nMean{.0},
		nStdDev{1.},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	Normal::Normal(double nNewStdDev) :
		nMean{.0},
		nStdDev{nNewStdDev},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	Normal::Normal(double nNewMean, double nNewStdDev) :
		nMean{nNewMean},
		nStdDev{nNewStdDev},
		sEngine{static_cast<std::mt19937_64::result_type>(std::chrono::system_clock::now().time_since_epoch().count())}
	{
		//Empty.
	}

	Normal::Normal(std::mt19937_64::result_type nSeed) :
		nMean{.0},
		nStdDev{1.},
		sEngine{nSeed}
	{
		//Empty.
	}

	Normal::Normal(std::mt19937_64::result_type nSeed, double nNewStdDev) :
		nMean{.0},
		nStdDev{nNewStdDev},
		sEngine{nSeed}
	{
		//Empty.
	}

	Normal::Normal(std::mt19937_64::result_type nSeed, double nNewMean, double nNewStdDev) :
		nMean{nNewMean},
		nStdDev{nNewStdDev},
		sEngine{nSeed}
	{
		//Empty.
	}

	Normal::Normal(const Normal &sSrc) :
		nMean{sSrc.nMean},
		nStdDev{sSrc.nStdDev},
		sEngine{sSrc.sEngine}
	{
		//Empty.
	}

	Normal::Normal(Normal &&sSrc) :
		nMean{sSrc.nMean},
		nStdDev{sSrc.nStdDev},
		sEngine{std::move(sSrc.sEngine)}
	{
		//Empty.
	}

	Normal &Normal::operator=(const Normal &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nMean = sSrc.nMean;
		this->nStdDev = sSrc.nStdDev;
		this->sEngine = sSrc.sEngine;

		return *this;
	}

	Normal &Normal::operator=(Normal &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nMean = sSrc.nMean;
		this->nStdDev = sSrc.nStdDev;
		this->sEngine = std::move(sSrc.sEngine);

		return *this;
	}

	//void Normal::initializeBias(Layer::LayerBase &sLayer)
	//{
	//	std::normal_distribution<double> sDist{this->nMean, this->nStdDev};
	//
	//	sLayer.initBias([this, &sDist]()
	//	{
	//		return static_cast<float>(sDist(this->sEngine));
	//	});
	//}
	//
	//void Normal::initializeWeight(Layer::LayerBase &sLayer)
	//{
	//	std::normal_distribution<double> sDist{this->nMean, this->nStdDev};
	//
	//	sLayer.initWeight([this, &sDist]()
	//	{
	//		return static_cast<float>(sDist(this->sEngine));
	//	});
	//}
}