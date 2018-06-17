
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CACHECONTAINER_H

#define _CLASS_TINNET_CACHECONTAINER_H

#include "TinNetDLL.h"

#include "Cache.h"

#include <cstdlib>
#include <memory>
#include <unordered_map>

namespace TinNet
{
	class TINNET_DLL CacheContainer final
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
			float *pPointer;

			inline CacheState(float *pPointer, std::size_t nSize) :
				pPointer{pPointer}
			{
				this->sCacheInfo.bDirty = true;
				this->sCacheInfo.sCache = Cache{pPointer, nSize};
			}

			inline ~CacheState()
			{
				_aligned_free(this->pPointer);
			}
		};

	private:
		std::unordered_map<CacheInfo *, std::unique_ptr<CacheState>> sCacheStateMap;

	public:
		CacheContainer() = default;
		CacheContainer(const CacheContainer &sSrc) = delete;
		CacheContainer(CacheContainer &&sSrc) = default;
		~CacheContainer() = default;
		
	public:
		CacheContainer &operator=(const CacheContainer &sSrc) = delete;
		CacheContainer &operator=(CacheContainer &&sSrc) = default;
		
	public:
		CacheInfo *request(std::size_t nSize);
		void release(CacheInfo *pCacheInfo);
		void setDirtyAll();
	};

	using CachePtr = CacheContainer::CacheInfo *;
}

#endif