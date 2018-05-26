
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "CacheContainer.h"

namespace TinNet::Graph
{
	CacheContainer::CacheInfo *CacheContainer::request(std::size_t nSize)
	{
		auto pPointer{std::make_unique<float[]>(nSize)};
		auto pCacheState{std::make_unique<CacheState>(CacheState{CacheInfo{true, Cache{pPointer.get(), nSize}}, std::move(pPointer)})};

		return this->sCacheStateMap.emplace(&pCacheState->sCacheInfo, std::move(pCacheState)).first->first;
	}

	void CacheContainer::release(CacheInfo *pCache)
	{
		this->sCacheStateMap.erase(pCache);
	}

	void CacheContainer::setDiryAll()
	{
		for (auto &sPair : this->sCacheStateMap)
			sPair.second->sCacheInfo.bDirty = true;
	}
}