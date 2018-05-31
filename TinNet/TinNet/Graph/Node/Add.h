
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_ADD_H

#define _CLASS_TINNET_GRAPH_NODE_ADD_H

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
	class TINNET_DLL Add final : public FullCachedGraphNode
	{
	private:
		Shape sShape;
		Iterator<Accessor, Accessor, Accessor> sIterator;

	public:
		Add(const std::string &sName, Graph *pGraph);
		Add(const Add &sSrc) = delete;
		~Add() = default;
		
	public:
		Add &operator=(const Add &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif