
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_NEGATIVEBP_H

#define _CLASS_TINNET_GRAPH_NODE_NEGATIVEBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Negative.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL NegativeBP final : public GraphNodeBP
	{
	public:
		NegativeBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		NegativeBP(const NegativeBP &sSrc) = default;
		NegativeBP(NegativeBP &&sSrc) = default;
		~NegativeBP() = default;
		
	public:
		NegativeBP &operator=(const NegativeBP &sSrc) = default;
		NegativeBP &operator=(NegativeBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif