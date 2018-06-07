
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_EXPBP_H

#define _CLASS_TINNET_GRAPH_NODE_EXPBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Exp.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL ExpBP final : public GraphNodeBP
	{
	public:
		ExpBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		ExpBP(const ExpBP &sSrc) = default;
		ExpBP(ExpBP &&sSrc) = default;
		~ExpBP() = default;
		
	public:
		ExpBP &operator=(const ExpBP &sSrc) = default;
		ExpBP &operator=(ExpBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif