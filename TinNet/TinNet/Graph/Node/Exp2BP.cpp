
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Exp2BP.h"

namespace TinNet::Graph::Node
{
	Exp2BP::Exp2BP(const std::string &sName, const GraphNodeBP *pLeftNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> Exp2BP::make(class Graph *pGraph) const
	{
		return std::make_unique<Exp2>(this->sName, pGraph);
	}
}