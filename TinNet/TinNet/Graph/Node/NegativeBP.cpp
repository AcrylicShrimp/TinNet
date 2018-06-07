
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "NegativeBP.h"

namespace TinNet::Graph::Node
{
	NegativeBP::NegativeBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> NegativeBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Negative>(this->sName, pGraph);
	}
}