
/*
	2018.05.26
	Created by AcrylicShrimp.
*/

#include "Graph.h"

#include "Node/Input.h"

namespace TinNet::Graph
{
	Graph::Graph(const GraphBP &sGraphBP)
	{
		for (const auto &sGraphNodeBP : sGraphBP)
		{
			if (this->sGraphNodeMap.find(sGraphNodeBP->name()) != this->sGraphNodeMap.cend())
				throw std::invalid_argument("this name is already in use");

			this->sGraphNodeMap.emplace(sGraphNodeBP->name(), sGraphNodeBP->instantiate(this));
		}

		for (auto &sPair : this->sGraphNodeMap)
			sPair.second->initGraph();
	}

	Graph::~Graph()
	{
		this->disableBackward();
	}

	void Graph::enableBackward()
	{
		for (auto &sPair : this->sGraphNodeMap)
			sPair.second->enableBackward();
	}

	void Graph::disableBackward()
	{
		for (auto &sPair : this->sGraphNodeMap)
			sPair.second->disableBackward();
	}

	const Cache *Graph::forward(GraphNode *pNode)
	{
		if (!pNode)
			return nullptr;

		this->sCacheContainer.setDiryAll();

		return &pNode->forward();
	}

	const Cache *Graph::forward(const std::string &sNodeName)
	{
		return this->forward(this->node(sNodeName));
	}

	const Cache *Graph::backward(GraphNode *pNode)
	{
		if (!pNode)
			return nullptr;

		this->sCacheContainer.setDiryAll();

		return &pNode->backward();
	}

	const Cache *Graph::backward(const std::string &sNodeName)
	{
		return this->backward(this->node(sNodeName));
	}

	Cache &Graph::input(const std::string &sInputName)
	{
		return this->node<Node::Input>(sInputName)->cache();
	}

	const Cache &Graph::input(const std::string &sInputName) const
	{
		return this->node<Node::Input>(sInputName)->cache();
	}
}