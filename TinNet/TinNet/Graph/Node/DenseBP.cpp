
/*
	2018.06.05
	Created by AcrylicShrimp.
*/

#include "DenseBP.h"

namespace TinNet::Graph::Node
{
	DenseBP::DenseBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, std::size_t nFanOut) :
		GraphNodeBP(sName),
		nFanOut{nFanOut}
	{
		this->asBackwardNode(pLeftNodeBP);
	}
	
	std::unique_ptr<GraphNode> DenseBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Dense>(this->sName, pGraph, this->nFanOut);
	}
}