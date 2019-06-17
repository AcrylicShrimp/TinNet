
/*
	2019.03.26
	Created by AcrylicShrimp.
*/

#include "Graph.h"

#include "../Node/Input.h"

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

	void Graph::feed(const std::vector<std::tuple<std::string, Core::Shape, Core::Span<float>>> &sFeedDataList)
	{
		for (const auto &sFeedData : sFeedDataList)
			this->node<Node::Input>(std::get<0>(sFeedData))->feed(std::get<1>(sFeedData), std::get<2>(sFeedData));
	}
}