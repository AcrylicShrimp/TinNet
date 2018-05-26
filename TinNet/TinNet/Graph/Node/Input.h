
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_INPUT_H

#define _CLASS_TINNET_GRAPH_NODE_INPUT_H

#include "../../TinNetDLL.h"

#include "../BackwardCachedGraphNode.h"
#include "../../Cache.h"
#include "../Graph.h"

#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Input final : public BackwardCachedGraphNode
	{
	protected:
		Cache sCache;
		std::size_t nFanOut;
		
	public:
		Input(const std::string &sName, Graph *pGraph, std::size_t nFanOut);
		Input(const Input &sSrc) = delete;
		~Input() = default;
		
	public:
		Input &operator=(const Input &sSrc) = delete;
		
	public:
		inline Cache &cache();
		inline const Cache &cache() const;
		virtual std::size_t fanOut() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void init() override;
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