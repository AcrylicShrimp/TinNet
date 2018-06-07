
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_LOG10BP_H

#define _CLASS_TINNET_GRAPH_NODE_LOG10BP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Log10.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Log10BP final : public GraphNodeBP
	{
	public:
		Log10BP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		Log10BP(const Log10BP &sSrc) = default;
		Log10BP(Log10BP &&sSrc) = default;
		~Log10BP() = default;

	public:
		Log10BP &operator=(const Log10BP &sSrc) = default;
		Log10BP &operator=(Log10BP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif