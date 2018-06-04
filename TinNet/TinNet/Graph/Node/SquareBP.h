
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SQUAREBP_H

#define _CLASS_TINNET_GRAPH_NODE_SQUAREBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Square.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL SquareBP final : public GraphNodeBP
	{
	public:
		SquareBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		SquareBP(const SquareBP &sSrc) = default;
		SquareBP(SquareBP &&sSrc) = default;
		~SquareBP() = default;
		
	public:
		SquareBP &operator=(const SquareBP &sSrc) = default;
		SquareBP &operator=(SquareBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif