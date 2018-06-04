
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_TANHBP_H

#define _CLASS_TINNET_GRAPH_NODE_TANHBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Tanh.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL TanhBP final : public GraphNodeBP
	{
	public:
		TanhBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		TanhBP(const TanhBP &sSrc) = default;
		TanhBP(TanhBP &&sSrc) = default;
		~TanhBP() = default;
		
	public:
		TanhBP &operator=(const TanhBP &sSrc) = default;
		TanhBP &operator=(TanhBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif