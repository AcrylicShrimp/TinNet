
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "SubtractBP.h"

namespace TinNet::Graph::Node
{
	SubtractBP::SubtractBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
		this->asBackwardNode(pRightNodeBP);
	}

	std::unique_ptr<GraphNode> SubtractBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Subtract>(this->sName, pGraph);
	}
}