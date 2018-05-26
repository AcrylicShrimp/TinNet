
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "AddBP.h"

namespace TinNet::Graph::Node
{
	AddBP::AddBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
		this->asBackwardNode(pRightNodeBP);
	}

	std::unique_ptr<GraphNode> AddBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Add>(this->sName, pGraph);
	}
}