
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_UNIFORM_H

#define _CLASS_TINNET_INITIALIZER_UNIFORM_H

#include "../TinNetDLL.h"

#include "../Layer/LayerBase.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace TinNet::Initializer
{
	class TINNET_DLL Uniform final
	{
	private:
		double nMin;
		double nMax;
		std::mt19937_64 sEngine;
		
	public:
		Uniform(double nNewMin, double nNewMax);
		Uniform(std::mt19937_64::result_type nSeed, double nNewMin, double nNewMax);
		Uniform(const Uniform &sSrc);
		Uniform(Uniform &&sSrc);
		~Uniform() = default;
		
	public:
		Uniform &operator=(const Uniform &sSrc);
		Uniform &operator=(Uniform &&sSrc);
		
	public:
		void initializeBias(Layer::LayerBase &sLayer);
		void initializeWeight(Layer::LayerBase &sLayer);
	};
}

#endif