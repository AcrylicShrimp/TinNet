
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

	Node &GraphBP::input(const Shape &sShape, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Input>(sName, sShape)};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::input(const Shape &sShape, std::vector<float> &sValue, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Input>(sName, sShape)};

		pNode->feed({sShape, sValue});
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::constant(float nValue, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Constant>(sName, Shape{}, std::vector<float>{nValue})};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::constant(const Shape &sShape, const std::vector<float> &sValue, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Constant>(sName, sShape, sValue)};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::reshape(Node &sLeft, const Shape &sShape, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Reshape>(sName, sShape)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::squeeze(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Squeeze>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::reduceSum(Node &sLeft, const std::vector<bool> &sAxis, bool bSqueeze, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::ReduceSum>(sName, sAxis, bSqueeze)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::abs(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Abs>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::neg(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Neg>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::sign(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Sign>(sName)};

		Node::link(&sLeft, pNode);
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

	Node &GraphBP::pow(Node &sLeft, Node &sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Pow>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::exp(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Exp>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::exp2(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Exp2>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::log(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Log>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::log2(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Log2>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::log10(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Log10>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::logn(Node &sLeft, float nBase, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::LogN>(sName, nBase)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::sin(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Sin>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::cos(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Cos>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	Node &GraphBP::tan(Node &sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Tan>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}
}