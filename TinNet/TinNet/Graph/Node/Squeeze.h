
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SQUEEZE_H

#define _CLASS_TINNET_GRAPH_NODE_SQUEEZE_H

#include "../../TinNetDLL.h"

#include "../../Accessor.h"
#include "../../Iterator.h"
#include "../../Shape.h"
#include "../Graph.h"
#include "../BackwardCachedGraphNode.h"

#include <cstddef>
#include <stdexcept>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Squeeze final : public BackwardCachedGraphNode
	{
	protected:
		Shape sShape;
		
	public:
		Squeeze(const std::string &sName, Graph *pGraph);
		Squeeze(const Squeeze &sSrc) = delete;
		~Squeeze() = default;
		
	public:
		Squeeze &operator=(const Squeeze &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void initGraph() override;
		virtual const Cache &forward() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif