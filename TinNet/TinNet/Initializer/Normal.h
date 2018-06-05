
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_NORMAL_H

#define _CLASS_TINNET_INITIALIZER_NORMAL_H

#include "../TinNetDLL.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace TinNet::Initializer
{
	class TINNET_DLL Normal final
	{
	private:
		double nMean;
		double nStdDev;
		std::mt19937_64 sEngine;

	public:
		Normal();
		Normal(double nNewStdDev);
		Normal(double nNewMean, double nNewStdDev);
		Normal(std::mt19937_64::result_type nSeed);
		Normal(std::mt19937_64::result_type nSeed, double nNewStdDev);
		Normal(std::mt19937_64::result_type nSeed, double nNewMean, double nNewStdDev);
		Normal(const Normal &sSrc);
		Normal(Normal &&sSrc);
		~Normal() = default;

	public:
		Normal &operator=(const Normal &sSrc);
		Normal &operator=(Normal &&sSrc);

	public:
		//void initializeBias(Layer::LayerBase &sLayer);
		//void initializeWeight(Layer::LayerBase &sLayer);
	};
}

#endif