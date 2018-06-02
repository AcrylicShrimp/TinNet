
/*
	2018.06.02
	Created by AcrylicShrimp.
*/

#include "MatMulBP.h"

namespace TinNet::Graph::Node
{
	MatMulBP::MatMulBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP) :
		GraphNodeBP(sName)
	{
		this->asBackwardNode(pLeftNodeBP);
		this->asBackwardNode(pRightNodeBP);
	}

	std::unique_ptr<GraphNode> MatMulBP::make(class Graph *pGraph) const
	{
		return std::make_unique<MatMul>(this->sName, pGraph);
	}
}