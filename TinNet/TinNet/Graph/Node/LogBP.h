
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_LOGBP_H

#define _CLASS_TINNET_GRAPH_NODE_LOGBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Log.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL LogBP final : public GraphNodeBP
	{
	public:
		LogBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		LogBP(const LogBP &sSrc) = default;
		LogBP(LogBP &&sSrc) = default;
		~LogBP() = default;
		
	public:
		LogBP &operator=(const LogBP &sSrc) = default;
		LogBP &operator=(LogBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif