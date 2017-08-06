
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_INITIALIZER_XAVIER_H

#define _CLASS_CAYSNET_INITIALIZER_XAVIER_H

#include "Layer.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace CaysNet::Initializer
{
	class Xavier final
	{
	private:
		std::mt19937_64 sEngine;
		
	public:
		Xavier();
		Xavier(std::mt19937_64::result_type nSeed);
		Xavier(const Xavier &sSrc);
		Xavier(Xavier &&sSrc);
		~Xavier() = default;
		
	public:
		Xavier &operator=(const Xavier &sSrc);
		Xavier &operator=(Xavier &&sSrc);
		
	public:
		void initializeBias(Layer &sLayer);
		void initializeWeight(Layer &sLayer);
	};
}

#endif