
/*
	2019.03.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_SUBTRACT_H

#define _CLASS_TINNET_NODE_SUBTRACT_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Subtract : public Node
	{
		TINNET_NODE_TYPE_DCL(Subtract)

	protected:
		NodeInput sInputLeft;
		NodeInput sInputRight;

	public:
		Subtract(Core::Graph *pGraph, std::string_view sName);
		Subtract(const Subtract &sSrc) = delete;
		virtual ~Subtract() noexcept = default;

	public:
		Subtract &operator=(const Subtract &sSrc) = delete;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpLeft(const Node *pDy);
		void __backwardOpRight(const Node *pDy);
	};
}

#endif