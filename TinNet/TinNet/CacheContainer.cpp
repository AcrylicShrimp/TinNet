
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "CacheContainer.h"

namespace TinNet
{
	CacheContainer::CacheInfo *CacheContainer::request(std::size_t nSize)
	{
		auto pPointer{reinterpret_cast<float *>(_aligned_malloc(nSize * sizeof(float), sizeof(float) * 8))};
		auto pCacheState{std::make_unique<CacheState>(pPointer, nSize)};

		return this->sCacheStateMap.emplace(&pCacheState->sCacheInfo, std::move(pCacheState)).first->first;
	}

	void CacheContainer::release(CacheContainer::CacheInfo *pCacheInfo)
	{
		this->sCacheStateMap.erase(pCacheInfo);
	}

	void CacheContainer::setDirtyAll()
	{
		for (auto &sPair : this->sCacheStateMap)
			sPair.second->sCacheInfo.bDirty = true;
	}
}