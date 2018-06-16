
/*
	2018.06.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SOFTMAX_H

#define _CLASS_TINNET_GRAPH_NODE_SOFTMAX_H

#include "../../TinNetDLL.h"

#include "../../Accessor.h"
#include "../../Iterator.h"
#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Softmax final : public FullCachedGraphNode
	{
	protected:
		Iterator<Accessor, Accessor> sIterator;
		std::vector<bool> sAxis;
		std::vector<float> sSum;
		std::vector<float> sSumBackward;
		Cache sSumCache;
		Cache sSumBackwardCache;
		
	public:
		Softmax(const std::string &sName, Graph *pGraph, const std::vector<bool> &sAxis);
		Softmax(const Softmax &sSrc) = delete;
		~Softmax() = default;
		
	public:
		Softmax &operator=(const Softmax &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif