
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SUBTRACT_H

#define _CLASS_TINNET_GRAPH_NODE_SUBTRACT_H

#include "../../TinNetDLL.h"

#include "../../Accessor.h"
#include "../../Iterator.h"
#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Subtract final : public FullCachedGraphNode
	{
	protected:
		Shape sShape;
		Iterator<Accessor, Accessor, Accessor> sIterator;

	public:
		Subtract(const std::string &sName, Graph *pGraph);
		Subtract(const Subtract &sSrc) = delete;
		~Subtract() = default;
		
	public:
		Subtract &operator=(const Subtract &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif