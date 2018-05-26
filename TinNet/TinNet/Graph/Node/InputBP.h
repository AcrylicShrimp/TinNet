
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_INPUTBP_H

#define _CLASS_TINNET_GRAPH_NODE_INPUTBP_H

#include "../../TinNetDLL.h"

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
		std::size_t nFanOut;
		
	public:
		InputBP(const std::string &sName, std::size_t nFanOut);
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