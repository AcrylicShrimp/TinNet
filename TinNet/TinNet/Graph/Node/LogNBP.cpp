
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "LogNBP.h"

namespace TinNet::Graph::Node
{
	LogNBP::LogNBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, float nBase) :
		GraphNodeBP(sName),
		nBase{nBase}
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> LogNBP::make(class Graph *pGraph) const
	{
		return std::make_unique<LogN>(this->sName, pGraph, this->nBase);
	}
}