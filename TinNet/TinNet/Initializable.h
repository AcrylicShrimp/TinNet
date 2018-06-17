
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZABLE_H

#define _CLASS_TINNET_INITIALIZABLE_H

#include "TinNetDLL.h"

#include <cstddef>
#include <functional>

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
	};
}

#endif