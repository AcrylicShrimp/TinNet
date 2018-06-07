
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_LOG2BP_H

#define _CLASS_TINNET_GRAPH_NODE_LOG2BP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Log2.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Log2BP final : public GraphNodeBP
	{
	public:
		Log2BP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		Log2BP(const Log2BP &sSrc) = default;
		Log2BP(Log2BP &&sSrc) = default;
		~Log2BP() = default;
		
	public:
		Log2BP &operator=(const Log2BP &sSrc) = default;
		Log2BP &operator=(Log2BP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif