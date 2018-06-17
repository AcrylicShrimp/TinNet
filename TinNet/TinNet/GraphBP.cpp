
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "GraphBP.h"

namespace TinNet
{
	GraphBP::GraphBP(Graph &sGraph) :
		sGraph{sGraph}
	{
		//Empty.
	}

	Node &GraphBP::input(Shape sShape, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Input>(sName, sShape)};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::constant(Shape sShape, const std::vector<float> &sValue, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Constant>(sName, sShape, sValue)};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::add(Node &sLeft, Node &sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Add>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::subtract(Node &sLeft, Node &sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Subtract>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::multiply(Node &sLeft, Node &sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Multiply>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::divide(Node &sLeft, Node &sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Divide>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}
}