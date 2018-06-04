
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "TanhBP.h"

namespace TinNet::Graph::Node
{
	TanhBP::TanhBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> TanhBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Tanh>(this->sName, pGraph);
	}
}