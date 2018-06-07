
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_LOG10_H

#define _CLASS_TINNET_GRAPH_NODE_LOG10_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cmath>
#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Log10 final : public FullCachedGraphNode
	{
	public:
		Log10(const std::string &sName, Graph *pGraph);
		Log10(const Log10 &sSrc) = delete;
		~Log10() = default;
		
	public:
		Log10 &operator=(const Log10 &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif