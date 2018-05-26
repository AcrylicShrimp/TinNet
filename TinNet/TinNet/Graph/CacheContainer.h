
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_CACHECONTAINER_H

#define _CLASS_TINNET_GRAPH_CACHECONTAINER_H

#include "../TinNetDLL.h"

#include "../Cache.h"

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
			std::unique_ptr<float[]> pPointer;
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