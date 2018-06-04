
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "ReLUBP.h"

namespace TinNet::Graph::Node
{
	ReLUBP::ReLUBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> ReLUBP::make(class Graph *pGraph) const
	{
		return std::make_unique<ReLU>(this->sName, pGraph);
	}
}