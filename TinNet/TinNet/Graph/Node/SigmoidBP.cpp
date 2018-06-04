
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "SigmoidBP.h"

namespace TinNet::Graph::Node
{
	SigmoidBP::SigmoidBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}
	
	std::unique_ptr<GraphNode> SigmoidBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Sigmoid>(this->sName, pGraph);
	}
}