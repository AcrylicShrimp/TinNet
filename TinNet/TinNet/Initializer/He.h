
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_HE_H

#define _CLASS_TINNET_INITIALIZER_HE_H

#include "../TinNetDLL.h"

#include "../Layer/Layer.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <random>
#include <utility>

namespace TinNet::Initializer
{
	class TINNET_DLL He final
	{
	private:
		std::mt19937_64 sEngine;

	public:
		He();
		He(std::mt19937_64::result_type nSeed);
		He(const He &sSrc);
		He(He &&sSrc);
		~He() = default;

	public:
		He &operator=(const He &sSrc);
		He &operator=(He &&sSrc);

	public:
		void initializeBias(Layer::Layer &sLayer);
		void initializeWeight(Layer::Layer &sLayer);
	};
}

#endif