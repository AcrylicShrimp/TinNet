
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_XAVIER_H

#define _CLASS_TINNET_INITIALIZER_XAVIER_H

#include "../TinNetDLL.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace TinNet::Initializer
{
	class TINNET_DLL Xavier final
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
		//void initializeBias(Layer::LayerBase &sLayer);
		//void initializeWeight(Layer::LayerBase &sLayer);
	};
}

#endif