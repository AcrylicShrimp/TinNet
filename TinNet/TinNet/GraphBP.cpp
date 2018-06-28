
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

	NodeRef GraphBP::input(const Shape &sShape, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Input>(sName, sShape)};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::select(NodeRef sLeft, NodeRef sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Select>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::constant(float nValue, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Constant>(sName, Shape{}, std::vector<float>{nValue})};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::constant(const Shape &sShape, const std::vector<float> &sValue, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Constant>(sName, sShape, sValue)};

		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::reshape(NodeRef sLeft, const Shape &sShape, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Reshape>(sName, sShape)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::squeeze(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Squeeze>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::reduceMin(NodeRef sLeft, const std::vector<bool> &sAxis, bool bSqueeze, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::ReduceMin>(sName, sAxis, bSqueeze)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::reduceMax(NodeRef sLeft, const std::vector<bool> &sAxis, bool bSqueeze, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::ReduceMax>(sName, sAxis, bSqueeze)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::reduceSum(NodeRef sLeft, const std::vector<bool> &sAxis, bool bSqueeze, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::ReduceSum>(sName, sAxis, bSqueeze)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::reduceMean(NodeRef sLeft, const std::vector<bool> &sAxis, bool bSqueeze, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::ReduceMean>(sName, sAxis, bSqueeze)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::abs(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Abs>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::neg(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Neg>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::sign(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Sign>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::add(NodeRef sLeft, NodeRef sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Add>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::subtract(NodeRef sLeft, NodeRef sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Subtract>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::multiply(NodeRef sLeft, NodeRef sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Multiply>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::divide(NodeRef sLeft, NodeRef sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Divide>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::pow(NodeRef sLeft, NodeRef sRight, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Pow>(sName)};

		Node::link(&sLeft, pNode);
		Node::link(&sRight, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::square(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Square>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::exp(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Exp>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::exp2(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Exp2>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::log(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Log>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::log2(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Log2>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::log10(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Log10>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::logn(NodeRef sLeft, float nBase, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::LogN>(sName, nBase)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::sin(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Sin>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::cos(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Cos>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::tan(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Tan>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::sinh(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Sinh>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::cosh(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Cosh>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::tanh(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Tanh>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::relu(NodeRef sLeft, float nAlpha, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::ReLU>(sName, nAlpha)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::softplus(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Softplus>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::softmax(NodeRef sLeft, const std::vector<bool> &sAxis, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Softmax>(sName, sAxis)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::sigmoid(NodeRef sLeft, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Sigmoid>(sName)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::dense(NodeRef sLeft, std::size_t nFanOut, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Dense>(sName, nullptr, nFanOut)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::dense(NodeRef sSharing, NodeRef sLeft, std::size_t nFanOut, const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Dense>(sName, &sSharing, nFanOut)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::convolution(NodeRef sLeft,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel,
		std::size_t nHStride,
		std::size_t nVStride,
		const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Convolution>(sName, nullptr, nKernelWidth, nKernelHeight, nHStride, nVStride, nOutputWidth, nOutputHeight, nOutputChannel)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::convolution(NodeRef sSharing, NodeRef sLeft,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel,
		std::size_t nHStride,
		std::size_t nVStride,
		const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::Convolution>(sName, &sSharing, nKernelWidth, nKernelHeight, nHStride, nVStride, nOutputWidth, nOutputHeight, nOutputChannel)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::dilatedConvolution(NodeRef sLeft,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nHDilated,
		std::size_t nVDilated,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel,
		std::size_t nHStride,
		std::size_t nVStride,
		const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::DilatedConvolution>(sName, nullptr, nKernelWidth, nKernelHeight, nHDilated, nVDilated, nHStride, nVStride, nOutputWidth, nOutputHeight, nOutputChannel)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::dilatedConvolution(NodeRef sSharing, NodeRef sLeft,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nHDilated,
		std::size_t nVDilated,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel,
		std::size_t nHStride,
		std::size_t nVStride,
		const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::DilatedConvolution>(sName, &sSharing, nKernelWidth, nKernelHeight, nHDilated, nVDilated, nHStride, nVStride, nOutputWidth, nOutputHeight, nOutputChannel)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::transposedConvolution(NodeRef sLeft,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel,
		std::size_t nHStride,
		std::size_t nVStride,
		const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::TransposedConvolution>(sName, nullptr, nKernelWidth, nKernelHeight, nHStride, nVStride, nOutputWidth, nOutputHeight, nOutputChannel)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}

	NodeRef GraphBP::transposedConvolution(NodeRef sSharing, NodeRef sLeft,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel,
		std::size_t nHStride,
		std::size_t nVStride,
		const std::string &sName)
	{
		auto pNode{this->sGraph.addNode<GraphNode::TransposedConvolution>(sName, &sSharing, nKernelWidth, nKernelHeight, nHStride, nVStride, nOutputWidth, nOutputHeight, nOutputChannel)};

		Node::link(&sLeft, pNode);
		pNode->notifyShapeUpdated();

		return *pNode;
	}
}