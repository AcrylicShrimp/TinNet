
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
		Node &constant(Shape sShape, const std::vector<float> &sValue, const std::string &sName = "");
		Node &add(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &subtract(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &multiply(Node &sLeft, Node &sRight, const std::string &sName = "");
		Node &divide(Node &sLeft, Node &sRight, const std::string &sName = "");
	};
}

#endif