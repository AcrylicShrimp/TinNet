
/*
	2019.07.31
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_NEGATIVE_H

#define _CLASS_TINNET_NODE_NEGATIVE_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <stdexcept>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Negative : public Node
	{
		TINNET_NODE_TYPE_DCL(Negative)

	protected:
		NodeInput sInput;
		
	public:
		Negative(Core::Graph *pGraph, std::string_view sName);
		Negative(const Negative &sSrc) = delete;
		virtual ~Negative() noexcept = default;
		
	public:
		Negative &operator=(const Negative &sSrc) = delete;
		
	public:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOp(const Node *pDy);
	};
}

#endif