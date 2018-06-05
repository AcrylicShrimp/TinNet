
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "BackwardCachedGraphNode.h"

namespace TinNet::Graph
{
	BackwardCachedGraphNode::BackwardCachedGraphNode(const std::string &sName, Graph *pGraph) :
		GraphNode(sName, pGraph),
		pBackward{nullptr},
		pBackwardTemp{nullptr}
	{
		//Empty.
	}

	void BackwardCachedGraphNode::enableBackward()
	{
		if (this->pBackward)
			return;

		if (this->pBackwardTemp)
			return;

		this->pBackward = this->pGraph->cacheContainer().request(this->shape().element());
		this->pBackwardTemp = this->pGraph->cacheContainer().request(this->shape().element());
	}

	void BackwardCachedGraphNode::disableBackward()
	{
		if (this->pBackward)
			this->pGraph->cacheContainer().release(this->pBackward);

		if (this->pBackwardTemp)
			this->pGraph->cacheContainer().release(this->pBackwardTemp);

		this->pBackward = nullptr;
		this->pBackwardTemp = nullptr;
	}

	const Cache &BackwardCachedGraphNode::backward()
	{
		this->computeBackward(this->pBackward, this->pBackwardTemp);

		return this->pBackward->sCache;
	}
}