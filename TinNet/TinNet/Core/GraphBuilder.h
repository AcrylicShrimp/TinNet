
/*
	2019.03.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_GRAPHBUILDER_H

#define _CLASS_TINNET_CORE_GRAPHBUILDER_H

#include "../TinNetDLL.h"

#include "NodeWrapper.h"
#include "Shape.h"
#include "Span.h"

#include "../Node/Node.h"

#include <cassert>
#include <initializer_list>
#include <sstream>
#include <string>

namespace TinNet::Core
{
	class Graph;

	class TINNET_DLL GraphBuilder final
	{
	public:
		Graph *const pGraph;

	public:
		GraphBuilder(Graph *pGraph);
		GraphBuilder(const GraphBuilder &sSrc) = default;
		~GraphBuilder() noexcept = default;

	public:
		GraphBuilder &operator=(const GraphBuilder &sSrc) = default;

	public:
		/*
			Type registration functions.
		*/
		void registerStandardNodeType();

		/*
			Front nodes.
		*/
		NodeWrapper input();
		NodeWrapper input(const std::string &sNodeName);
		NodeWrapper parameter(const Shape &sShape);
		NodeWrapper parameter(const std::string &sNodeName, const Shape &sShape);

		/*
			Basic arithmetic nodes.
		*/
		NodeWrapper add(NodeWrapper sLeft, NodeWrapper sRight);
		NodeWrapper add(const std::string &sNodeName, NodeWrapper sLeft, NodeWrapper sRight);

		/*
			BLAS nodes.
		*/
		NodeWrapper mm(NodeWrapper sLeft, NodeWrapper sRight);
		NodeWrapper mm(const std::string &sNodeName, NodeWrapper sLeft, NodeWrapper sRight);

		/*
			Math function nodes.
		*/
		NodeWrapper sigmoid(NodeWrapper sLogit);
		NodeWrapper sigmoid(const std::string &sNodeName, NodeWrapper sLogit);

		/*
			Loss nodes.
		*/
		NodeWrapper mse(NodeWrapper sLabel, NodeWrapper sPred);
		NodeWrapper mse(const std::string &sNodeName, NodeWrapper sLabel, NodeWrapper sPred);
		NodeWrapper sigmoidCE(NodeWrapper sLabel, NodeWrapper sProb);
		NodeWrapper sigmoidCE(const std::string &sNodeName, NodeWrapper sLabel, NodeWrapper sProb);
	};
}

#endif