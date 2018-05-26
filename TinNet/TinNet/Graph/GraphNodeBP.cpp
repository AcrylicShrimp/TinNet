
/*
	2018.05.26
	Created by AcrylicShrimp.
*/

#include "GraphNodeBP.h"

#include "Graph.h"

namespace TinNet::Graph
{
	GraphNodeBP::GraphNodeBP(const std::string &sName) :
		sName{sName}
	{
		//Empty.
	}

	std::unique_ptr<GraphNode> GraphNodeBP::instantiate(Graph *pGraph) const
	{
		auto pNode = this->make(pGraph);

		for (const auto *pBackwardBP : this->sBackwardBPList)
		{
			auto pBackwardNode = pGraph->node(pBackwardBP->name());

			if (!pBackwardNode)
				throw std::logic_error("undefined node");

			GraphNode::link(pBackwardNode, pNode.get());
		}

		return pNode;
	}
}