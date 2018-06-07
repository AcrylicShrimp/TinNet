
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Log10BP.h"

namespace TinNet::Graph::Node
{
	Log10BP::Log10BP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> Log10BP::make(class Graph *pGraph) const
	{
		return std::make_unique<Log10>(this->sName, pGraph);
	}
}