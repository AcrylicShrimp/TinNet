
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_NEGATIVE_H

#define _CLASS_TINNET_GRAPH_NODE_NEGATIVE_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Negative final : public FullCachedGraphNode
	{
	public:
		Negative(const std::string &sName, Graph *pGraph);
		Negative(const Negative &sSrc) = delete;
		~Negative() = default;
		
	public:
		Negative &operator=(const Negative &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif