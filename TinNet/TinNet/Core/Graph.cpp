
/*
	2019.03.26
	Created by AcrylicShrimp.
*/

#include "Graph.h"

namespace TinNet::Core
{
	Graph::Graph() :
		sBuilder{this}
	{
		this->sBuilder.registerStandardNodeType();
	}

	std::vector<Node::Node *> Graph::nodes(const Node::NodeType *pNodeType)
	{
		std::vector<Node::Node *> sResult;

		for (auto sPair{this->sNodeTypeMap.equal_range(pNodeType)}; sPair.first != sPair.second; ++sPair.first)
			sResult.emplace_back(sPair.first->second);

		return sResult;
	}

	std::vector<const Node::Node *> Graph::nodes(const Node::NodeType *pNodeType) const
	{
		std::vector<const Node::Node *> sResult;

		for (auto sPair{this->sNodeTypeMap.equal_range(pNodeType)}; sPair.first != sPair.second; ++sPair.first)
			sResult.emplace_back(sPair.first->second);

		return sResult;
	}
}