
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "BackwardCachedGraphNode.h"

namespace TinNet::Graph
{
	BackwardCachedGraphNode::BackwardCachedGraphNode(const std::string &sName, Graph *pGraph) :
		GraphNode(sName, pGraph),
		pBackwardCacheInfo{nullptr},
		pBackwardTempCacheInfo{nullptr}
	{
		//Empty.
	}

	void BackwardCachedGraphNode::enableBackward()
	{
		this->disableBackward();
		this->pBackwardCacheInfo = this->pGraph->cacheContainer().request(this->fanOut());
		this->pBackwardTempCacheInfo = this->pGraph->cacheContainer().request(this->fanOut());
	}

	void BackwardCachedGraphNode::disableBackward()
	{
		if (this->pBackwardCacheInfo)
			this->pGraph->cacheContainer().release(this->pBackwardCacheInfo);

		if (this->pBackwardTempCacheInfo)
			this->pGraph->cacheContainer().release(this->pBackwardTempCacheInfo);

		this->pBackwardCacheInfo = nullptr;
		this->pBackwardTempCacheInfo = nullptr;
	}

	const Cache &BackwardCachedGraphNode::backward()
	{
		this->computeBackward(this->pBackwardCacheInfo, this->pBackwardTempCacheInfo);

		return this->pBackwardCacheInfo->sCache;
	}
}