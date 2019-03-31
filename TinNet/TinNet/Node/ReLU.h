
/*
	2019.03.28
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_RELU_H

#define _CLASS_TINNET_NODE_RELU_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL ReLU : public Node
	{
		TINNET_NODE_TYPE_DCL(ReLU)

	public:
		const float nAlpha;

	protected:
		NodeInput sInputLogit;

	public:
		ReLU(Core::Graph *pGraph, std::string_view sName, float nAlpha);
		ReLU(const ReLU &sSrc) = delete;
		virtual ~ReLU() noexcept = default;

	public:
		ReLU &operator=(const ReLU &sSrc) = delete;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOp(const Node *pDy);
	};
}

#endif