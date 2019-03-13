
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_SIGMOID_H

#define _CLASS_TINNET_NODE_SIGMOID_H

#include "../TinNetDLL.h"

#include "Node.h"
#include "NodeInput.h"

#include <cmath>
#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Sigmoid : public Node
	{
	protected:
		NodeInput sInputLogit;

	public:
		Sigmoid(std::string_view sName);
		Sigmoid(const Sigmoid &sSrc) = delete;
		virtual ~Sigmoid() noexcept = default;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOp(const Node *pDy);
	};
}

#endif