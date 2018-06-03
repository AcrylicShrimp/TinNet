
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#include "SqueezeBP.h"

namespace TinNet::Graph::Node
{
	SqueezeBP::SqueezeBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> SqueezeBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Squeeze>(this->sName, pGraph);
	}
}