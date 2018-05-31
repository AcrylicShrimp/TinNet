
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_INPUT_H

#define _CLASS_TINNET_GRAPH_NODE_INPUT_H

#include "../../TinNetDLL.h"

#include "../../Cache.h"
#include "../../Shape.h"
#include "../BackwardCachedGraphNode.h"
#include "../Graph.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Input final : public BackwardCachedGraphNode
	{
	protected:
		Cache sCache;
		Shape sShape;
		
	public:
		Input(const std::string &sName, Graph *pGraph, const Shape &sShape);
		Input(const Input &sSrc) = delete;
		~Input() = default;
		
	public:
		Input &operator=(const Input &sSrc) = delete;
		
	public:
		inline Cache &cache();
		inline const Cache &cache() const;
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void initGraph() override;
		virtual const Cache &forward() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};

	inline Cache &Input::cache()
	{
		return this->sCache;
	}

	inline const Cache &Input::cache() const
	{
		return this->sCache;
	}
}

#endif