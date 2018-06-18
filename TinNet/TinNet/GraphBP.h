
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
		Node &input(Shape sShape, const std::string &sName = "");
		Node &constant(float nValue, const std::string &sName = "");
		Node &constant(Shape sShape, const std::vector<float> &sValue, const std::string &sName = "");
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
	};
}

#endif