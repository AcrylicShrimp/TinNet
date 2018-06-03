
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#include "ReduceSumBP.h"

namespace TinNet::Graph::Node
{
	ReduceSumBP::ReduceSumBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const std::vector<bool> sAxis, bool bSqueeze) :
		GraphNodeBP(sName),
		sAxis{sAxis},
		bSqueeze{bSqueeze}
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> ReduceSumBP::make(class Graph *pGraph) const
	{
		return std::make_unique<ReduceSum>(this->sName, pGraph, this->sAxis, bSqueeze);
	}
}