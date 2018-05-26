
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "FullCachedGraphNode.h"

namespace TinNet::Graph
{
	FullCachedGraphNode::FullCachedGraphNode(const std::string &sName, Graph *pGraph) :
		BackwardCachedGraphNode(sName, pGraph),
		pForwardCacheInfo{nullptr}
	{
		//Empty.
	}

	FullCachedGraphNode::~FullCachedGraphNode()
	{
		if (this->pForwardCacheInfo)
			this->pGraph->cacheContainer().release(this->pForwardCacheInfo);

		this->pForwardCacheInfo = nullptr;
	}

	void FullCachedGraphNode::init()
	{
		if (this->pForwardCacheInfo)
			return;

		this->pForwardCacheInfo = this->pGraph->cacheContainer().request(this->fanOut());
	}

	const Cache &FullCachedGraphNode::forward()
	{
		this->computeForward(this->pForwardCacheInfo);

		return this->pForwardCacheInfo->sCache;
	}
}