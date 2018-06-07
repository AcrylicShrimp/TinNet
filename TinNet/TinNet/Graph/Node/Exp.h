
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_EXP_H

#define _CLASS_TINNET_GRAPH_NODE_EXP_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../Graph.h"
#include "../FullCachedGraphNode.h"

#include <cmath>
#include <cstddef>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Exp final : public FullCachedGraphNode
	{
	public:
		Exp(const std::string &sName, Graph *pGraph);
		Exp(const Exp &sSrc) = delete;
		~Exp() = default;
		
	public:
		Exp &operator=(const Exp &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
	};
}

#endif