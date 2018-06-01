
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_RESHAPEBP_H

#define _CLASS_TINNET_GRAPH_NODE_RESHAPEBP_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../GraphNodeBP.h"
#include "Reshape.h"

#include <cstddef>
#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL ReshapeBP final : public GraphNodeBP
	{
	protected:
		Shape sShape;
		
	public:
		ReshapeBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const Shape &sShape);
		ReshapeBP(const ReshapeBP &sSrc) = default;
		ReshapeBP(ReshapeBP &&sSrc) = default;
		~ReshapeBP() = default;
		
	public:
		ReshapeBP &operator=(const ReshapeBP &sSrc) = default;
		ReshapeBP &operator=(ReshapeBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif