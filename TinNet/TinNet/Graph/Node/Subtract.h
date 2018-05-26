
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SUBTRACT_H

#define _CLASS_TINNET_GRAPH_NODE_SUBTRACT_H

#include "../../TinNetDLL.h"

#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Subtract final : public FullCachedGraphNode
	{
	public:
		Subtract(const std::string &sName, Graph *pGraph);
		Subtract(const Subtract &sSrc) = delete;
		~Subtract() = default;
		
	public:
		Subtract &operator=(const Subtract &sSrc) = delete;
		
	public:
		virtual std::size_t fanOut() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif