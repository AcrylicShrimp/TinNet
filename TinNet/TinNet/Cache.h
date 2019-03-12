
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CACHE_H

#define _CLASS_TINNET_CACHE_H

#include "TinNetDLL.h"

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace TinNet
{
	class TINNET_DLL Cache final
	{
	private:
		float *pBase;
		std::size_t nSize;

	public:
		Cache();
		Cache(std::vector<float> &sVector);
		Cache(float *pBase, const float *pEnd);
		Cache(float *pBase, std::size_t nSize);
		Cache(const Cache &sSrc);
		~Cache() = default;

	public:
		Cache &operator=(const Cache &sSrc);
		Cache &operator=(std::vector<float> &sVector);
		inline operator float *();
		inline operator const float *() const;

	public:
		inline float *begin();
		inline const float *begin() const;
		inline const float *cbegin() const;
		inline float *end();
		inline const float *end() const;
		inline const float *cend() const;
		inline std::size_t size() const;
		void zero();
		void one();
		void fill(float nValue);
		void copy(Cache sCache);
		void copy(Cache sCache, float nFactor);
		void copyNegative(Cache sCache);
		float accumulate() const;
		void accumulate(Cache sCache);
		void accumulate(Cache sCache, float nFactor);
		std::string toString() const;
		std::string toString(std::size_t nMaxIndex) const;
	};

	inline Cache operator+(Cache &sLeft, std::size_t nRight);
	inline Cache operator+(std::size_t nLeft, Cache &sRight);

	inline Cache::operator float *()
	{
		return this->pBase;
	}

	inline Cache::operator const float *() const
	{
		return this->pBase;
	}

	inline float *Cache::begin()
	{
		return this->pBase;
	}

	inline const float *Cache::begin() const
	{
		return this->pBase;
	}

	inline const float *Cache::cbegin() const
	{
		return this->pBase;
	}

	inline float *Cache::end()
	{
		return this->pBase + this->nSize;
	}

	inline const float *Cache::end() const
	{
		return this->pBase + this->nSize;
	}

	inline const float *Cache::cend() const
	{
		return this->pBase + this->nSize;
	}

	inline std::size_t Cache::size() const
	{
		return this->nSize;
	}

	inline Cache operator+(Cache &sLeft, std::size_t nRight)
	{
		return Cache{sLeft.begin() + nRight, sLeft.size() < nRight ? 0 : sLeft.size() - nRight};
	}

	inline Cache operator+(std::size_t nLeft, Cache &sRight)
	{
		return Cache{sRight.begin() + nLeft, sRight.size() < nLeft ? 0 : sRight.size() - nLeft};
	}
}

#endif