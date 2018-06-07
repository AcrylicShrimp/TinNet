
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_LOGNBP_H

#define _CLASS_TINNET_GRAPH_NODE_LOGNBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "LogN.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL LogNBP final : public GraphNodeBP
	{
	protected:
		float nBase;

	public:
		LogNBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, float nBase);
		LogNBP(const LogNBP &sSrc) = default;
		LogNBP(LogNBP &&sSrc) = default;
		~LogNBP() = default;
		
	public:
		LogNBP &operator=(const LogNBP &sSrc) = default;
		LogNBP &operator=(LogNBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif