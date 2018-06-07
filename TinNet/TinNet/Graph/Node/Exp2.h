
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_EXP2_H

#define _CLASS_TINNET_GRAPH_NODE_EXP2_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cmath>
#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Exp2 final : public FullCachedGraphNode
	{
	public:
		Exp2(const std::string &sName, Graph *pGraph);
		Exp2(const Exp2 &sSrc) = delete;
		~Exp2() = default;

	public:
		Exp2 &operator=(const Exp2 &sSrc) = delete;

	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif