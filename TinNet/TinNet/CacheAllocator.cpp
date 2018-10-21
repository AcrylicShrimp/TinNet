
/*
	2018.09.02
	Created by AcrylicShrimp.
*/

#include "CacheAllocator.h"

namespace TinNet
{
	CacheAllocator::CacheInfo *CacheAllocator::allocate(std::size_t nSize)
	{
		auto pCacheState{std::make_unique<CacheState>(nSize)};

		return this->sCacheStateMap.emplace(&pCacheState->sCacheInfo, std::move(pCacheState)).first->first;
	}

	void CacheAllocator::deallocate(CacheAllocator::CacheInfo *pCacheInfo)
	{
		this->sCacheStateMap.erase(pCacheInfo);
	}

	void CacheAllocator::setDirtyAll()
	{
		for (auto &sPair : this->sCacheStateMap)
			sPair.second->sCacheInfo.bDirty = true;
	}
}