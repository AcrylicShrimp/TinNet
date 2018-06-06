
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "CacheContainer.h"

namespace TinNet::Graph
{
	CacheContainer::CacheInfo *CacheContainer::request(std::size_t nSize)
	{
		auto pPointer{reinterpret_cast<float *>(_aligned_malloc(nSize * sizeof(float), sizeof(float) * 4))};
		auto pCacheState{std::make_unique<CacheState>(pPointer, nSize)};
		
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