
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_MULTIPLYBP_H

#define _CLASS_TINNET_GRAPH_NODE_MULTIPLYBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Multiply.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL MultiplyBP final : public GraphNodeBP
	{
	public:
		MultiplyBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP);
		MultiplyBP(const MultiplyBP &sSrc) = default;
		MultiplyBP(MultiplyBP &&sSrc) = default;
		~MultiplyBP() = default;
		
	public:
		MultiplyBP &operator=(const MultiplyBP &sSrc) = default;
		MultiplyBP &operator=(MultiplyBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif