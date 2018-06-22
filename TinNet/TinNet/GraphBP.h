
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
		Node &input(const Shape &sShape, const std::string &sName = "");
		Node &input(const Shape &sShape, std::vector<float> &sValue, const std::string &sName = "");
		Node &constant(float nValue, const std::string &sName = "");
		Node &constant(const Shape &sShape, const std::vector<float> &sValue, const std::string &sName = "");
		Node &reshape(Node &sLeft, const Shape &sShape, const std::string &sName = "");
		Node &squeeze(Node &sLeft, const std::string &sName = "");
		Node &reduceMin(Node &sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		Node &reduceMax(Node &sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		Node &reduceSum(Node &sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		Node &reduceMean(Node &sLeft, const std::vector<bool> &sAxis = {}, bool bSqueeze = true, const std::string &sName = "");
		Node &abs(Node &sLeft, const std::string &sName = "");
		Node &neg(Node &sLeft, const std::string &sName = "");
		Node &sign(Node &sLeft, const std::string &sName = "");
		Node &add(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &subtract(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &multiply(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &divide(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &pow(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &square(Node &sLeft, const std::string &sName = "");
		Node &exp(Node &sLeft, const std::string &sName = "");
		Node &exp2(Node &sLeft, const std::string &sName = "");
		Node &log(Node &sLeft, const std::string &sName = "");
		Node &log2(Node &sLeft, const std::string &sName = "");
		Node &log10(Node &sLeft, const std::string &sName = "");
		Node &logn(Node &sLeft, float nBase, const std::string &sName = "");
		Node &sin(Node &sLeft, const std::string &sName = "");
		Node &cos(Node &sLeft, const std::string &sName = "");
		Node &tan(Node &sLeft, const std::string &sName = "");
		Node &sinh(Node &sLeft, const std::string &sName = "");
		Node &cosh(Node &sLeft, const std::string &sName = "");
		Node &tanh(Node &sLeft, const std::string &sName = "");
		Node &relu(Node &sLeft, float nAlpha = .0f, const std::string &sName = "");
		Node &softplus(Node &sLeft, const std::string &sName = "");
		Node &softmax(Node &sLeft, const std::vector<bool> &sAxis = {}, const std::string &sName = "");
		Node &sigmoid(Node &sLeft, const std::string &sName = "");
		Node &dense(Node &sLeft, std::size_t nFanOut, const std::string &sName = "");
		Node &convolution(Node &sLeft,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nOutputWidth ,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride = 1,
			std::size_t nVStride = 1,
			const std::string &sName = "");
		Node &dilatedConvolution(Node &sLeft,
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
	};
}

#endif