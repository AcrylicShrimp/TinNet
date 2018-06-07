
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "ExpBP.h"

namespace TinNet::Graph::Node
{
	ExpBP::ExpBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> ExpBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Exp>(this->sName, pGraph);
	}
}