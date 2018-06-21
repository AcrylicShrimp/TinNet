
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZABLE_H

#define _CLASS_TINNET_INITIALIZABLE_H

#include "TinNetDLL.h"

#include "Cache.h"
#include "CacheContainer.h"

#include <cstddef>
#include <functional>
#include <vector>

namespace TinNet
{
	using InitializablePtr = class Initializable *;

	class TINNET_DLL Initializable
	{
	public:
		Initializable(class Graph *pGraph);
		Initializable(const Initializable &sSrc) = delete;
		virtual ~Initializable() = default;
		
	public:
		Initializable &operator=(const Initializable &sSrc) = delete;
		
	public:
		virtual std::size_t fanIn() const = 0;
		virtual std::size_t fanOut() const = 0;
		virtual void initialize(std::function<float()> fInitializer) = 0;
		virtual void variablePass() = 0;
		virtual void applyGradient(float nFactor) = 0;
		virtual std::vector<std::size_t> &gradientSizeList() = 0;
		virtual std::vector<CachePtr> &gradientList() = 0;
	};
}

#endif