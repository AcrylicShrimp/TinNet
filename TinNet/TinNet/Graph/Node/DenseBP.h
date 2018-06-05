
/*
	2018.06.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_DENSEBP_H

#define _CLASS_TINNET_GRAPH_NODE_DENSEBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Dense.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL DenseBP final : public GraphNodeBP
	{
	protected:
		std::size_t nFanOut;

	public:
		DenseBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, std::size_t nFanOut);
		DenseBP(const DenseBP &sSrc) = default;
		DenseBP(DenseBP &&sSrc) = default;
		~DenseBP() = default;
		
	public:
		DenseBP &operator=(const DenseBP &sSrc) = default;
		DenseBP &operator=(DenseBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif