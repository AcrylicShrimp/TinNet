
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#include "Xavier.h"

namespace TinNet::Initializer
{
	Xavier::Xavier(std::size_t nFanIn, std::size_t nFanOut) :
		sEngine{static_cast<std::mt19937_64::result_type>(std::random_device{}())},
		sDist{.0f, std::sqrt(2.f / (nFanIn + nFanOut))}
	{
		//Empty.
	}

	Xavier::Xavier(std::mt19937_64::result_type nSeed, std::size_t nFanIn, std::size_t nFanOut) :
		sEngine{nSeed},
		sDist{.0f, std::sqrt(2.f / (nFanIn + nFanOut))}
	{
		//Empty.
	}

	void Xavier::operator()(Core::Span<float> sSpan)
	{
		for (auto &nValue : sSpan)
			nValue = this->sDist(this->sEngine);
	}
}