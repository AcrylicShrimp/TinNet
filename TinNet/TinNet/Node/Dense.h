
/*
	2019.03.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_DENSE_H

#define _CLASS_TINNET_NODE_DENSE_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"
#include "../Core/Shape.h"
#include "../Core/Span.h"

#include "../Compute/GEMM.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <stdexcept>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Dense : public Node
	{
		TINNET_NODE_TYPE_DCL(Dense)

	protected:
		NodeInput sInput;
		NodeInput sInputWeight;
		NodeInput sInputBias;

	public:
		Dense(Core::Graph *pGraph, std::string_view sName);
		Dense(const Dense &sSrc) = delete;
		virtual ~Dense() noexcept = default;

	public:
		Dense &operator=(const Dense &sSrc) = delete;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpInput(const Node *pDy);
		void __backwardOpWeight(const Node *pDy);
		void __backwardOpBias(const Node *pDy);
	};
}

#endif