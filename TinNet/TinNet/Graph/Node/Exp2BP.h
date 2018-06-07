
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_EXP2BP_H

#define _CLASS_TINNET_GRAPH_NODE_EXP2BP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Exp2.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Exp2BP final : public GraphNodeBP
	{
	public:
		Exp2BP(const std::string &sName, const GraphNodeBP *pLeftNodeBP);
		Exp2BP(const Exp2BP &sSrc) = default;
		Exp2BP(Exp2BP &&sSrc) = default;
		~Exp2BP() = default;
		
	public:
		Exp2BP &operator=(const Exp2BP &sSrc) = default;
		Exp2BP &operator=(Exp2BP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif