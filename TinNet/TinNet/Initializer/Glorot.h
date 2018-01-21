
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_GLOROT_H

#define _CLASS_TINNET_INITIALIZER_GLOROT_H

#include "../TinNetDLL.h"

#include "../Layer/LayerBase.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace TinNet::Initializer
{
	class TINNET_DLL Glorot final
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
		void initializeBias(Layer::LayerBase &sLayer);
		void initializeWeight(Layer::LayerBase &sLayer);
	};
}

#endif