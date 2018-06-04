
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SIGMOIDBP_H

#define _CLASS_TINNET_GRAPH_NODE_SIGMOIDBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Sigmoid.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL SigmoidBP final : public GraphNodeBP
	{
	public:
		SigmoidBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		SigmoidBP(const SigmoidBP &sSrc) = default;
		SigmoidBP(SigmoidBP &&sSrc) = default;
		~SigmoidBP() = default;
		
	public:
		SigmoidBP &operator=(const SigmoidBP &sSrc) = default;
		SigmoidBP &operator=(SigmoidBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif