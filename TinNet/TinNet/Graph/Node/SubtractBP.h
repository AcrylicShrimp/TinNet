
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SUBTRACTBP_H

#define _CLASS_TINNET_GRAPH_NODE_SUBTRACTBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Subtract.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL SubtractBP final : public GraphNodeBP
	{
	public:
		SubtractBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP);
		SubtractBP(const SubtractBP &sSrc) = default;
		SubtractBP(SubtractBP &&sSrc) = default;
		~SubtractBP() = default;
		
	public:
		SubtractBP &operator=(const SubtractBP &sSrc) = default;
		SubtractBP &operator=(SubtractBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif