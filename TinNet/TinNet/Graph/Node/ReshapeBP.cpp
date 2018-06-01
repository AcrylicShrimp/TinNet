
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#include "ReshapeBP.h"

namespace TinNet::Graph::Node
{
	ReshapeBP::ReshapeBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const Shape &sShape) :
		GraphNodeBP(sName),
		sShape{sShape}
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> ReshapeBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Reshape>(this->sName, pGraph, this->sShape);
	}
}