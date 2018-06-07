
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Log2BP.h"

namespace TinNet::Graph::Node
{
	Log2BP::Log2BP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> Log2BP::make(class Graph *pGraph) const
	{
		return std::make_unique<Log2>(this->sName, pGraph);
	}
}