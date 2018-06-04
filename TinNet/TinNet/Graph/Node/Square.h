
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SQUARE_H

#define _CLASS_TINNET_GRAPH_NODE_SQUARE_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Square final : public FullCachedGraphNode
	{
	public:
		Square(const std::string &sName, Graph *pGraph);
		Square(const Square &sSrc) = delete;
		~Square() = default;
		
	public:
		Square &operator=(const Square &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif