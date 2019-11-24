
/*
	2019.07.31
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_MULTIPLY_H

#define _CLASS_TINNET_NODE_MULTIPLY_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <stdexcept>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Multiply : public Node
	{
		TINNET_NODE_TYPE_DCL(Multiply)

	protected:
		NodeInput sInputLeft;
		NodeInput sInputRight;
		
	public:
		Multiply(Core::Graph *pGraph, std::string_view sName);
		Multiply(const Multiply &sSrc) = delete;
		virtual ~Multiply() noexcept = default;
		
	public:
		Multiply &operator=(const Multiply &sSrc) = delete;
		
	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpLeft(const Node *pDy);
		void __backwardOpRight(const Node *pDy);
	};
}

#endif