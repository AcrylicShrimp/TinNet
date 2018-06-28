
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHBP_H

#define _CLASS_TINNET_GRAPHBP_H

#include "TinNetDLL.h"

#include "Graph.h"
#include "Node.h"
#include "Shape.h"
#include "GraphNode/GraphNode.h"

#include <cstddef>
#include <string>
#include <vector>

namespace TinNet
{
	class TINNET_DLL GraphBP final
	{
	private:
		Graph &sGraph;
		
	public:
		GraphBP(Graph &sGraph);
		GraphBP(const GraphBP &sSrc) = default;
		~GraphBP() = default;
		
	public:
		GraphBP &operator=(const GraphBP &sSrc) = default;
		
	public:
		NodeRef input(const Shape &sShape, const std::string &sName = "");
		NodeRef select(NodeRef sLeft, NodeRef sRight, const std::string &sName = "");
		NodeRef constant(float nValue, const std::string &sName = "");
		NodeRef constant(const Shape &sShape, const std::vector<float> &sValue, const std::string &sName = "");
		NodeRef reshape(NodeRef sLeft, const Shape &sShape, const std::string &sName = "");
		NodeRef squeeze(NodeRef sLeft, const std::string &sName = "");
		NodeRef reduceMin(NodeRef sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		NodeRef reduceMax(NodeRef sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		NodeRef reduceSum(NodeRef sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		NodeRef reduceMean(NodeRef sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		NodeRef abs(NodeRef sLeft, const std::string &sName = "");
		NodeRef neg(NodeRef sLeft, const std::string &sName = "");
		NodeRef sign(NodeRef sLeft, const std::string &sName = "");
		NodeRef add(NodeRef sLeft, NodeRef sRight, const std::string &sName = "");
		NodeRef subtract(NodeRef sLeft, NodeRef sRight, const std::string &sName = "");
		NodeRef multiply(NodeRef sLeft, NodeRef sRight, const std::string &sName = "");
		NodeRef divide(NodeRef sLeft, NodeRef sRight, const std::string &sName = "");
		NodeRef pow(NodeRef sLeft, NodeRef sRight, const std::string &sName = "");
		NodeRef square(NodeRef sLeft, const std::string &sName = "");
		NodeRef exp(NodeRef sLeft, const std::string &sName = "");
		NodeRef exp2(NodeRef sLeft, const std::string &sName = "");
		NodeRef log(NodeRef sLeft, const std::string &sName = "");
		NodeRef log2(NodeRef sLeft, const std::string &sName = "");
		NodeRef log10(NodeRef sLeft, const std::string &sName = "");
		NodeRef logn(NodeRef sLeft, float nBase, const std::string &sName = "");
		NodeRef sin(NodeRef sLeft, const std::string &sName = "");
		NodeRef cos(NodeRef sLeft, const std::string &sName = "");
		NodeRef tan(NodeRef sLeft, const std::string &sName = "");
		NodeRef sinh(NodeRef sLeft, const std::string &sName = "");
		NodeRef cosh(NodeRef sLeft, const std::string &sName = "");
		NodeRef tanh(NodeRef sLeft, const std::string &sName = "");
		NodeRef relu(NodeRef sLeft, float nAlpha = .0f, const std::string &sName = "");
		NodeRef softplus(NodeRef sLeft, const std::string &sName = "");
		NodeRef softmax(NodeRef sLeft, const std::vector<bool> &sAxis = {}, const std::string &sName = "");
		NodeRef sigmoid(NodeRef sLeft, const std::string &sName = "");
		NodeRef dense(NodeRef sLeft, std::size_t nFanOut, const std::string &sName = "");
		NodeRef dense(NodeRef sSharing, NodeRef sLeft, std::size_t nFanOut, const std::string &sName = "");
		NodeRef convolution(NodeRef sLeft,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nOutputWidth ,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride = 1,
			std::size_t nVStride = 1,
			const std::string &sName = "");
		NodeRef convolution(NodeRef sSharing, NodeRef sLeft,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride = 1,
			std::size_t nVStride = 1,
			const std::string &sName = "");
		NodeRef dilatedConvolution(NodeRef sLeft,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nHDilated,
			std::size_t nVDilated,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride = 1,
			std::size_t nVStride = 1,
			const std::string &sName = "");
		NodeRef dilatedConvolution(NodeRef sSharing, NodeRef sLeft,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nHDilated,
			std::size_t nVDilated,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride = 1,
			std::size_t nVStride = 1,
			const std::string &sName = "");
		NodeRef transposedConvolution(NodeRef sLeft,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride = 1,
			std::size_t nVStride = 1,
			const std::string &sName = "");
		NodeRef transposedConvolution(NodeRef sSharing, NodeRef sLeft,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride = 1,
			std::size_t nVStride = 1,
			const std::string &sName = "");
	};
}

#endif