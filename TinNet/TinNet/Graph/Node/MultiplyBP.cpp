
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "MultiplyBP.h"

namespace TinNet::Graph::Node
{
	MultiplyBP::MultiplyBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
		this->asBackwardNode(pRightNodeBP);
	}

	std::unique_ptr<GraphNode> MultiplyBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Multiply>(this->sName, pGraph);
	}
}