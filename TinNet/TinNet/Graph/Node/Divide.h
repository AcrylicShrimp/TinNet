
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_DIVIDE_H

#define _CLASS_TINNET_GRAPH_NODE_DIVIDE_H

#include "../../TinNetDLL.h"

#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Divide final : public FullCachedGraphNode
	{
	public:
		Divide(const std::string &sName, Graph *pGraph);
		Divide(const Divide &sSrc) = delete;
		~Divide() = default;
		
	public:
		Divide &operator=(const Divide &sSrc) = delete;
		
	public:
		virtual std::size_t fanOut() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif