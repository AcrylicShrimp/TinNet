
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_REDUCESUMBP_H

#define _CLASS_TINNET_GRAPH_NODE_REDUCESUMBP_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../GraphNodeBP.h"
#include "ReduceSum.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace TinNet::Graph::Node
{
	class TINNET_DLL ReduceSumBP final : public GraphNodeBP
	{
	protected:
		std::vector<bool> sAxis;
		bool bSqueeze;
		
	public:
		ReduceSumBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const std::vector<bool> sAxis = {}, bool bSqueeze = true);
		ReduceSumBP(const ReduceSumBP &sSrc) = default;
		ReduceSumBP(ReduceSumBP &&sSrc) = default;
		~ReduceSumBP() = default;
		
	public:
		ReduceSumBP &operator=(const ReduceSumBP &sSrc) = default;
		ReduceSumBP &operator=(ReduceSumBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif