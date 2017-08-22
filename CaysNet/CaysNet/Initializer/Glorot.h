
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_INITIALIZER_GLOROT_H

#define _CLASS_CAYSNET_INITIALIZER_GLOROT_H

#include "../CaysNetDLL.h"

#include "../Layer.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace CaysNet::Initializer
{
	class CAYSNET_DLL Glorot final
	{
	private:
		std::mt19937_64 sEngine;
		
	public:
		Glorot();
		Glorot(std::mt19937_64::result_type nSeed);
		Glorot(const Glorot &sSrc);
		Glorot(Glorot &&sSrc);
		~Glorot() = default;
		
	public:
		Glorot &operator=(const Glorot &sSrc);
		Glorot &operator=(Glorot &&sSrc);
		
	public:
		void initializeBias(Layer &sLayer);
		void initializeWeight(Layer &sLayer);
	};
}

#endif