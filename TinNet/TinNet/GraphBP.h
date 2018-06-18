
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
		Node &softPlus(Node &sLeft, const std::string &sName = "");
		Node &sigmoid(Node &sLeft, const std::string &sName = "");
	};
}

#endif