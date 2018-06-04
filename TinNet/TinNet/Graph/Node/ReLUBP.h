
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_RELUBP_H

#define _CLASS_TINNET_GRAPH_NODE_RELUBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "ReLU.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL ReLUBP final : public GraphNodeBP
	{
	public:
		ReLUBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		ReLUBP(const ReLUBP &sSrc) = default;
		ReLUBP(ReLUBP &&sSrc) = default;
		~ReLUBP() = default;
		
	public:
		ReLUBP &operator=(const ReLUBP &sSrc) = default;
		ReLUBP &operator=(ReLUBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif