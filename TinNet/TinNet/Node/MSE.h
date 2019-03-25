
/*
	2019.03.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_MSE_H

#define _CLASS_TINNET_NODE_MSE_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cmath>
#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL MSE : public Node
	{
		TINNET_NODE_TYPE_DCL(MSE)

	protected:
		NodeInput sInputLabel;
		NodeInput sInputPrediction;

	public:
		MSE(Core::Graph *pGraph, std::string_view sName);
		MSE(const MSE &sSrc) = delete;
		virtual ~MSE() noexcept = default;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpLabel(const Node *pDy);
		void __backwardOpPrediction(const Node *pDy);
	};
}

#endif