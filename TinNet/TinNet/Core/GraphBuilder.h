
/*
	2019.03.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_GRAPHBUILDER_H

#define _CLASS_TINNET_CORE_GRAPHBUILDER_H

#include "../TinNetDLL.h"

#include "InitializerWrapper.h"
#include "NodeWrapper.h"
#include "Shape.h"
#include "Span.h"

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <sstream>
#include <string>
#include <vector>

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
		NodeWrapper parameter(const Shape &sShape, InitializerWrapper sInitializer);
		NodeWrapper parameter(const std::string &sNodeName, const Shape &sShape, InitializerWrapper sInitializer);

		/*
			Basic arithmetic nodes.
		*/
		NodeWrapper add(NodeWrapper sLeft, NodeWrapper sRight);
		NodeWrapper add(const std::string &sNodeName, NodeWrapper sLeft, NodeWrapper sRight);
		NodeWrapper subtract(NodeWrapper sLeft, NodeWrapper sRight);
		NodeWrapper subtract(const std::string &sNodeName, NodeWrapper sLeft, NodeWrapper sRight);

		/*
			Math function nodes.
		*/
		NodeWrapper relu(NodeWrapper sLogit, float nAlpha = .0f);
		NodeWrapper relu(const std::string &sNodeName, NodeWrapper sLogit, float nAlpha = .0f);
		NodeWrapper sigmoid(NodeWrapper sLogit);
		NodeWrapper sigmoid(const std::string &sNodeName, NodeWrapper sLogit);

		/*
			Reduce nodes.
		*/
		NodeWrapper sum(NodeWrapper sInput, bool bSqueeze);
		NodeWrapper sum(NodeWrapper sInput, bool bSqueeze, const std::vector<bool> &sReduceAxis);
		NodeWrapper sum(const std::string &sNodeName, NodeWrapper sInput, bool bSqueeze);
		NodeWrapper sum(const std::string &sNodeName, NodeWrapper sInput, bool bSqueeze, const std::vector<bool> &sReduceAxis);

		/*
			BLAS nodes.
		*/
		NodeWrapper mm(NodeWrapper sLeft, NodeWrapper sRight);
		NodeWrapper mm(const std::string &sNodeName, NodeWrapper sLeft, NodeWrapper sRight);

		/*
			Layers.
		*/
		NodeWrapper dense(NodeWrapper sInput, NodeWrapper sWeight, NodeWrapper sBias);
		NodeWrapper dense(const std::string &sNodeName, NodeWrapper sInput, NodeWrapper sWeight, NodeWrapper sBias);

		/*
			Loss nodes.
		*/
		NodeWrapper mse(NodeWrapper sLabel, NodeWrapper sPred);
		NodeWrapper mse(const std::string &sNodeName, NodeWrapper sLabel, NodeWrapper sPred);
		NodeWrapper sigmoidCE(NodeWrapper sLabel, NodeWrapper sProb);
		NodeWrapper sigmoidCE(const std::string &sNodeName, NodeWrapper sLabel, NodeWrapper sProb);

		/*
			Initializers.
		*/
		InitializerWrapper initConstant(float nConstant = .0f);
		InitializerWrapper initXavier(std::size_t nFanIn, std::size_t nFanOut);
	};

	NodeWrapper TINNET_DLL operator+(NodeWrapper sLeft, NodeWrapper sRight);
	NodeWrapper TINNET_DLL operator-(NodeWrapper sLeft, NodeWrapper sRight);
}

#endif