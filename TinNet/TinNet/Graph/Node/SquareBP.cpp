
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "SquareBP.h"

namespace TinNet::Graph::Node
{
	SquareBP::SquareBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> SquareBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Square>(this->sName, pGraph);
	}
}