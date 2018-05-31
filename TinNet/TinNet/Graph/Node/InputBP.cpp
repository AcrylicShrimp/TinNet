
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "InputBP.h"

namespace TinNet::Graph::Node
{
	InputBP::InputBP(const std::string &sName, const Shape &sShape) :
		GraphNodeBP(sName),
		sShape{sShape}
	{
		//Empty.
	}

	std::unique_ptr<GraphNode> InputBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Input>(this->sName, pGraph, this->sShape);
	}
}