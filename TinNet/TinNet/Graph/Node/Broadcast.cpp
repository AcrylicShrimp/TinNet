
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Broadcast.h"

namespace TinNet::Graph::Node
{
	Broadcast::Broadcast(const std::string &sName, Graph *pGraph, std::size_t nFanOut) :
		FullCachedGraphNode(sName, pGraph),
		nFanOut{nFanOut}
	{
		//Empty.
	}

	std::size_t Broadcast::fanOut() const
	{
		return this->nFanOut;
	}

	std::size_t Broadcast::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Broadcast::forwardPass(Cache sDestination)
	{
		sDestination.fill(this->sBackwardList.front()->forward()[0]);
	}

	void Broadcast::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination[0] = this->backward().accumulate();
	}
}