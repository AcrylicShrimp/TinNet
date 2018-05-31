
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_INPUTBP_H

#define _CLASS_TINNET_GRAPH_NODE_INPUTBP_H

#include "../../TinNetDLL.h"

#include "../../Shape.h"
#include "../GraphNodeBP.h"
#include "Input.h"

#include <cstddef>
#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL InputBP final : public GraphNodeBP
	{
	protected:
		Shape sShape;
		
	public:
		InputBP(const std::string &sName, const Shape &sShape);
		InputBP(const InputBP &sSrc) = default;
		InputBP(InputBP &&sSrc) = default;
		~InputBP() = default;
		
	public:
		InputBP &operator=(const InputBP &sSrc) = default;
		InputBP &operator=(InputBP &&sSrc) = default;
		
	protected:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif