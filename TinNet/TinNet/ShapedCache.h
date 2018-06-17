
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_SHAPEDCACHE_H

#define _CLASS_TINNET_SHAPEDCACHE_H

#include "TinNetDLL.h"

#include "Cache.h"
#include "Shape.h"

namespace TinNet
{
	class TINNET_DLL ShapedCache final
	{
	private:
		Shape sShape;
		Cache sCache;
		
	public:
		ShapedCache() = default;
		ShapedCache(const Shape &sShape);
		ShapedCache(const Shape &sShape, Cache sCache);
		ShapedCache(const ShapedCache &sSrc) = default;
		ShapedCache(ShapedCache &&sSrc) = default;
		~ShapedCache() = default;
		
	public:
		ShapedCache &operator=(const ShapedCache &sSrc) = default;
		ShapedCache &operator=(ShapedCache &&sSrc) = default;
		
	public:
		inline const Shape &shape() const;
		inline Cache cache() const;
		inline void set(const Shape &sShape, Cache sCache);
		inline void set(const Shape &sShape);
		inline void set(Cache sCache);
	};

	inline const Shape &ShapedCache::shape() const
	{
		return this->sShape;
	}

	inline Cache ShapedCache::cache() const
	{
		return this->sCache;
	}

	inline void ShapedCache::set(const Shape &sShape, Cache sCache)
	{
		this->sShape = sShape;
		this->sCache = sCache;
	}

	inline void ShapedCache::set(const Shape &sShape)
	{
		this->sShape = sShape;
	}

	inline void ShapedCache::set(Cache sCache)
	{
		this->sCache = sCache;
	}
}

#endif