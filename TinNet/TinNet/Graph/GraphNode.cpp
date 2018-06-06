
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "GraphNode.h"

#include "Graph.h"

namespace TinNet::Graph
{
	GraphNode::GraphNode(const std::string &sName, Graph *pGraph) :
		sName{sName},
		pGraph{pGraph}
	{
		if (!this->pGraph)
			throw std::invalid_argument("graph cannot be null");
	}

	std::size_t GraphNode::maxBackwardNodeCount() const
	{
		return std::numeric_limits<std::size_t>::max();
	}

	void GraphNode::link(GraphNode *pBackward, GraphNode *pForward)
	{
		if (!pBackward || !pForward)
			return;

		if (pBackward->pGraph != pForward->pGraph)
			throw std::invalid_argument("graph must be same object");

		if (pForward->maxBackwardNodeCount() <= pForward->backwardNodeCount())
			throw std::invalid_argument("forward node cannot have backward node anymore");

		pBackward->sForwardList.emplace_back(pForward);
		pForward->sBackwardList.emplace_back(pBackward);
	}

	void GraphNode::unlink(GraphNode *pBackward, GraphNode *pForward)
	{
		if (!pBackward || !pForward)
			return;

		auto iBackwardIndex{std::find(pBackward->sForwardList.cbegin(), pBackward->sForwardList.cend(), pForward)};
		auto iForwardIndex{std::find(pForward->sBackwardList.cbegin(), pForward->sBackwardList.cend(), pBackward)};

		if (iBackwardIndex != pBackward->sForwardList.cend())
			pBackward->sForwardList.erase(iBackwardIndex);

		if (iForwardIndex != pForward->sBackwardList.cend())
			pForward->sBackwardList.erase(iForwardIndex);
	}

	void GraphNode::computeForward(CacheContainer::CacheInfo *pDestination)
	{
		if (!pDestination->bDirty)
			return;

		this->forwardPass(pDestination->sCache);

		pDestination->bDirty = false;
	}

	void GraphNode::computeBackward(CacheContainer::CacheInfo *pDestination, CacheContainer::CacheInfo *pTemporary)
	{
		if (!pDestination->bDirty)
			return;

		if (this->isLeafForward())
		{
			pDestination->sCache.one();
			pDestination->bDirty = false;
			pTemporary->bDirty = false;

			return;
		}

		pDestination->sCache.zero();

		for (auto pForward : this->sForwardList)
		{
			pForward->backwardPass(this, pTemporary->sCache);
			pDestination->sCache.accumulate(pTemporary->sCache);
		}

		pDestination->bDirty = false;
		pTemporary->bDirty = false;
	}
}