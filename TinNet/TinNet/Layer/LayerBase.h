
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_LAYERBASE_H

#define _CLASS_TINNET_LAYER_LAYERBASE_H

#include "../TinNetDLL.h"

#include <cstddef>
#include <functional>

namespace TinNet::Layer
{
	class TINNET_DLL LayerBase
	{
	public:
		LayerBase() = default;
		virtual ~LayerBase() = default;
		
	public:
		virtual std::size_t fanIn() const = 0;
		virtual std::size_t fanOut() const = 0;
		virtual void initBias(std::function<float()> sGenerator) = 0;
		virtual void initWeight(std::function<float()> sGenerator) = 0;
	};
}

#endif