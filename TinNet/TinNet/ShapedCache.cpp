
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "ShapedCache.h"

namespace TinNet
{
	ShapedCache::ShapedCache(const Shape &sShape) :
		sShape{sShape}
	{
		//Empty.
	}

	ShapedCache::ShapedCache(const Shape &sShape, Cache sCache) :
		sShape{sShape},
		sCache{sCache}
	{
		//Empty.
	}
}