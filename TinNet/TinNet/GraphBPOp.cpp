
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "GraphBPOp.h"

TinNet::Node &operator+(TinNet::Node &sLeft)
{
	return sLeft;
}

TinNet::Node &operator-(TinNet::Node &sLeft)
{
	return sLeft;
}

TinNet::Node &operator+(TinNet::Node &sLeft, float nRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Add>("")};
	auto pConstant{sLeft.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nRight})};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(pConstant, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator+(float nLeft, TinNet::Node &sRight)
{
	auto pConstant{sRight.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nLeft})};
	auto pNode{sRight.graph()->addNode<TinNet::GraphNode::Add>("")};

	TinNet::Node::link(pConstant, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator+(TinNet::Node &sLeft, TinNet::Node &sRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Add>("")};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator-(TinNet::Node &sLeft, float nRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Subtract>("")};
	auto pConstant{sLeft.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nRight})};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(pConstant, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator-(float nLeft, TinNet::Node &sRight)
{
	auto pConstant{sRight.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nLeft})};
	auto pNode{sRight.graph()->addNode<TinNet::GraphNode::Subtract>("")};

	TinNet::Node::link(pConstant, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator-(TinNet::Node &sLeft, TinNet::Node &sRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Subtract>("")};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator*(TinNet::Node &sLeft, float nRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Multiply>("")};
	auto pConstant{sLeft.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nRight})};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(pConstant, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator*(float nLeft, TinNet::Node &sRight)
{
	auto pConstant{sRight.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nLeft})};
	auto pNode{sRight.graph()->addNode<TinNet::GraphNode::Multiply>("")};

	TinNet::Node::link(pConstant, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator*(TinNet::Node &sLeft, TinNet::Node &sRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Multiply>("")};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator/(TinNet::Node &sLeft, float nRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Divide>("")};
	auto pConstant{sLeft.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nRight})};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(pConstant, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator/(float nLeft, TinNet::Node &sRight)
{
	auto pConstant{sRight.graph()->addNode<TinNet::GraphNode::Constant>("", TinNet::Shape{}, std::vector<float>{nLeft})};
	auto pNode{sRight.graph()->addNode<TinNet::GraphNode::Divide>("")};

	TinNet::Node::link(pConstant, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}

TinNet::Node &operator/(TinNet::Node &sLeft, TinNet::Node &sRight)
{
	auto pNode{sLeft.graph()->addNode<TinNet::GraphNode::Divide>("")};

	TinNet::Node::link(&sLeft, pNode);
	TinNet::Node::link(&sRight, pNode);
	pNode->notifyShapeUpdated();

	return *pNode;
}