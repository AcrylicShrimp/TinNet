
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SQUEEZEBP_H

#define _CLASS_TINNET_GRAPH_NODE_SQUEEZEBP_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../GraphNodeBP.h"
#include "Squeeze.h"

#include <cstddef>
#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL SqueezeBP final : public GraphNodeBP
	{
	public:
		SqueezeBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		SqueezeBP(const SqueezeBP &sSrc) = default;
		SqueezeBP(SqueezeBP &&sSrc) = default;
		~SqueezeBP() = default;
		
	public:
		SqueezeBP &operator=(const SqueezeBP &sSrc) = default;
		SqueezeBP &operator=(SqueezeBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif