
/*
	2018.06.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_MATMUL_H

#define _CLASS_TINNET_GRAPH_NODE_MATMUL_H

#include "../../TinNetDLL.h"

#include "../../Accessor.h"
#include "../../Iterator.h"
#include "../../Shape.h"
#include "../Graph.h"
#include "../GraphOp.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <stdexcept>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL MatMul final : public FullCachedGraphNode
	{
	protected:
		Shape sShape;
		Iterator<Accessor, Accessor, Accessor> sIterator;
		
	public:
		MatMul(const std::string &sName, Graph *pGraph);
		MatMul(const MatMul &sSrc) = delete;
		~MatMul() = default;
		
	public:
		MatMul &operator=(const MatMul &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif