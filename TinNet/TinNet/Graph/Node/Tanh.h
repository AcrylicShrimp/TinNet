
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_TANH_H

#define _CLASS_TINNET_GRAPH_NODE_TANH_H

#include "../../TinNetDLL.h"

#include "../../Accessor.h"
#include "../../Iterator.h"
#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cmath>
#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Tanh final : public FullCachedGraphNode
	{
	protected:
		Iterator<Accessor> sIterator;
		
	public:
		Tanh(const std::string &sName, Graph *pGraph);
		Tanh(const Tanh &sSrc) = delete;
		~Tanh() = default;
		
	public:
		Tanh &operator=(const Tanh &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif