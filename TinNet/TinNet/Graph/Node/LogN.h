
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_LOGN_H

#define _CLASS_TINNET_GRAPH_NODE_LOGN_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cmath>
#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL LogN final : public FullCachedGraphNode
	{
	protected:
		float nLogBase;

	public:
		LogN(const std::string &sName, Graph *pGraph, float nBase);
		LogN(const LogN &sSrc) = delete;
		~LogN() = default;
		
	public:
		LogN &operator=(const LogN &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif