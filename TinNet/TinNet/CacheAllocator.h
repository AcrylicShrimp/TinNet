
/*
	2018.09.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CACHEALLOCATOR_H

#define _CLASS_TINNET_CACHEALLOCATOR_H

#include "TinNetDLL.h"

#include "Cache.h"

#include <cstddef>
#include <memory>
#include <unordered_map>

namespace TinNet
{
	class TINNET_DLL CacheAllocator
	{
	public:
		struct CacheInfo
		{
			bool bDirty;
			Cache sCache;
		};

		struct CacheState
		{
			CacheInfo sCacheInfo;
			std::unique_ptr<float[]> pPointer;

			inline CacheState(std::size_t nSize) :
				pPointer{std::make_unique<float[]>(nSize)}
			{
				this->sCacheInfo.bDirty = true;
				this->sCacheInfo.sCache = Cache{this->pPointer.get(), nSize};
			}
		};

	private:
		std::unordered_map<CacheInfo *, std::unique_ptr<CacheState>> sCacheStateMap;
		
	public:
		CacheAllocator() = default;
		CacheAllocator(const CacheAllocator &sSrc) = delete;
		CacheAllocator(CacheAllocator &&sSrc) = default;
		~CacheAllocator() = default;
		
	public:
		CacheAllocator &operator=(const CacheAllocator &sSrc) = delete;
		CacheAllocator &operator=(CacheAllocator &&sSrc) = default;
		
	public:
		CacheInfo *allocate(std::size_t nSize);
		void deallocate(CacheInfo *pCacheInfo);
		void setDirtyAll();
	};

	using CachePtr = CacheAllocator::CacheInfo *;
}

#endif