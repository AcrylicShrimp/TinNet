
/*
	2018.06.16
	Created by AcrylicShrimp.
*/

#include "SoftmaxBP.h"

namespace TinNet::Graph::Node
{
	SoftmaxBP::SoftmaxBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const std::vector<bool> sAxis) :
		GraphNodeBP(sName),
		sAxis{sAxis}
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> SoftmaxBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Softmax>(this->sName, pGraph, this->sAxis);
	}
}