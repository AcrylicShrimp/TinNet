
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_DENSE_H

#define _CLASS_TINNET_GRAPH_NODE_DENSE_H

#include "../../TinNetDLL.h"

#include "../../Accessor.h"
#include "../../Cache.h"
#include "../../Iterator.h"
#include "../../Shape.h"
#include "../CacheContainer.h"
#include "../Graph.h"
#include "../GraphOp.h"
#include "../VariableGraphNode.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Dense final : public VariableGraphNode
	{
	protected:
		Shape sInputShape;
		Shape sOutputShape;
		Shape sWeightShape;
		Iterator<Accessor, Accessor> sBiasIterator;
		Iterator<Accessor, Accessor, Accessor> sWeightIterator;
		
	public:
		Dense(const std::string &sName, Graph *pGraph, std::size_t nFanOut);
		Dense(const Dense &sSrc) = delete;
		~Dense() = default;
		
	public:
		Dense &operator=(const Dense &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
		virtual std::size_t fanIn() const override;
		virtual std::size_t fanOut() const override;
		virtual void backwardVariablePass() override;
	};
}

#endif