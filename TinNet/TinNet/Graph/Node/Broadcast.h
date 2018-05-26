
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_BROADCAST_H

#define _CLASS_TINNET_GRAPH_NODE_BROADCAST_H

#include "../../TinNetDLL.h"

#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Broadcast : public FullCachedGraphNode
	{
	private:
		std::size_t nFanOut;
		
	public:
		Broadcast(const std::string &sName, Graph *pGraph, std::size_t nFanOut);
		Broadcast(const Broadcast &sSrc) = delete;
		~Broadcast() = default;
		
	public:
		Broadcast &operator=(const Broadcast &sSrc) = delete;
		
	public:
		virtual std::size_t fanOut() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif