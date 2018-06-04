
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SIGMOID_H

#define _CLASS_TINNET_GRAPH_NODE_SIGMOID_H

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
	class TINNET_DLL Sigmoid final : public FullCachedGraphNode
	{
	protected:
		Iterator<Accessor> sIterator;
		
	public:
		Sigmoid(const std::string &sName, Graph *pGraph);
		Sigmoid(const Sigmoid &sSrc) = delete;
		~Sigmoid() = default;
		
	public:
		Sigmoid &operator=(const Sigmoid &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif