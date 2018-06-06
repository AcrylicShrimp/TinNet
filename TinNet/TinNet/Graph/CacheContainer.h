
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_CACHECONTAINER_H

#define _CLASS_TINNET_GRAPH_CACHECONTAINER_H

#include "../TinNetDLL.h"

#include "../Cache.h"

#include <cstdlib>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace TinNet::Graph
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
				sCacheInfo.bDirty = true;
				sCacheInfo.sCache = Cache{pPointer, nSize};
			}

			inline ~CacheState()
			{
				_aligned_free(pPointer);
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
		void release(CacheInfo *pCache);
		void setDiryAll();
	};
}

#endif