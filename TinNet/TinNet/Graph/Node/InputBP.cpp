
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "InputBP.h"

namespace TinNet::Graph::Node
{
	InputBP::InputBP(const std::string &sName, std::size_t nFanOut) :
		GraphNodeBP(sName),
		nFanOut{nFanOut}
	{
		//Empty.
	}

	std::unique_ptr<GraphNode> InputBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Input>(this->sName, pGraph, this->nFanOut);
	}
}