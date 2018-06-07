
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_RELU_H

#define _CLASS_TINNET_GRAPH_NODE_RELU_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL ReLU final : public FullCachedGraphNode
	{
	public:
		ReLU(const std::string &sName, Graph *pGraph);
		ReLU(const ReLU &sSrc) = delete;
		~ReLU() = default;
		
	public:
		ReLU &operator=(const ReLU &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif