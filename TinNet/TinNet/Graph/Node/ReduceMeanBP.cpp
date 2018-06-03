
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#include "ReduceMeanBP.h"

namespace TinNet::Graph::Node
{
	ReduceMeanBP::ReduceMeanBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const std::vector<bool> sAxis, bool bSqueeze) :
		GraphNodeBP(sName),
		sAxis{sAxis},
		bSqueeze{bSqueeze}
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> ReduceMeanBP::make(class Graph *pGraph) const
	{
		return std::make_unique<ReduceMean>(this->sName, pGraph, this->sAxis, bSqueeze);
	}
}