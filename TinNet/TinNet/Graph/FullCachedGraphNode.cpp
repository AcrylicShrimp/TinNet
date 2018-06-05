
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "FullCachedGraphNode.h"

namespace TinNet::Graph
{
	FullCachedGraphNode::FullCachedGraphNode(const std::string &sName, Graph *pGraph) :
		BackwardCachedGraphNode(sName, pGraph),
		pForward{nullptr}
	{
		//Empty.
	}

	FullCachedGraphNode::~FullCachedGraphNode()
	{
		if (this->pForward)
			this->pGraph->cacheContainer().release(this->pForward);

		this->pForward = nullptr;
	}

	void FullCachedGraphNode::initGraph()
	{
		if (this->pForward)
			return;

		this->pForward = this->pGraph->cacheContainer().request(this->shape().element());
	}

	const Cache &FullCachedGraphNode::forward()
	{
		this->computeForward(this->pForward);

		return this->pForward->sCache;
	}
}