
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_ADDBP_H

#define _CLASS_TINNET_GRAPH_NODE_ADDBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Add.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL AddBP final : public GraphNodeBP
	{
	public:
		AddBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP);
		AddBP(const AddBP &sSrc) = default;
		AddBP(AddBP &&sSrc) = default;
		~AddBP() = default;
		
	public:
		AddBP &operator=(const AddBP &sSrc) = default;
		AddBP &operator=(AddBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif