
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "LogBP.h"

namespace TinNet::Graph::Node
{
	LogBP::LogBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> LogBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Log>(this->sName, pGraph);
	}
}