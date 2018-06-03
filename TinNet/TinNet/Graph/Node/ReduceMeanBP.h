
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_REDUCEMEANBP_H

#define _CLASS_TINNET_GRAPH_NODE_REDUCEMEANBP_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../GraphNodeBP.h"
#include "ReduceMean.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace TinNet::Graph::Node
{
	class TINNET_DLL ReduceMeanBP final : public GraphNodeBP
	{
	protected:
		std::vector<bool> sAxis;
		bool bSqueeze;
		
	public:
		ReduceMeanBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const std::vector<bool> sAxis = {}, bool bSqueeze = true);
		ReduceMeanBP(const ReduceMeanBP &sSrc) = default;
		ReduceMeanBP(ReduceMeanBP &&sSrc) = default;
		~ReduceMeanBP() = default;
		
	public:
		ReduceMeanBP &operator=(const ReduceMeanBP &sSrc) = default;
		ReduceMeanBP &operator=(ReduceMeanBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif