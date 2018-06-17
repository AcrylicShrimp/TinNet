
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_FEEDABLE_H

#define _CLASS_TINNET_FEEDABLE_H

#include "TinNetDLL.h"

#include "ShapedCache.h"

namespace TinNet
{
	using FeedablePtr = class Feedable *;

	class TINNET_DLL Feedable
	{
	public:
		Feedable(class Graph *pGraph);
		Feedable(const Feedable &sSrc) = delete;
		virtual ~Feedable() = default;
		
	public:
		Feedable &operator=(const Feedable &sSrc) = delete;
		
	public:
		virtual void feed(ShapedCache sShapedCache) = 0;
	};
}

#endif