
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_DIVIDEBP_H

#define _CLASS_TINNET_GRAPH_NODE_DIVIDEBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Divide.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL DivideBP final : public GraphNodeBP
	{
	public:
		DivideBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP);
		DivideBP(const DivideBP &sSrc) = default;
		DivideBP(DivideBP &&sSrc) = default;
		~DivideBP() = default;

	public:
		DivideBP &operator=(const DivideBP &sSrc) = default;
		DivideBP &operator=(DivideBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif