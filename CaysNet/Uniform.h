
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_INITIALIZER_UNIFORM_H

#define _CLASS_CAYSNET_INITIALIZER_UNIFORM_H

#include "Layer.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace CaysNet::Initializer
{
	class Uniform final
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
		void initializeBias(Layer &sLayer);
		void initializeWeight(Layer &sLayer);
	};
}

#endif