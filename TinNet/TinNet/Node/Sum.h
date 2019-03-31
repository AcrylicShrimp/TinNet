
/*
	2019.03.31
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_SUM_H

#define _CLASS_TINNET_NODE_SUM_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Sum : public Node
	{
		TINNET_NODE_TYPE_DCL(Sum)

	protected:
		NodeInput sInput;
		
	public:
		Sum(Core::Graph *pGraph, std::string_view sName);
		Sum(const Sum &sSrc) = delete;
		virtual ~Sum() noexcept = default;
		
	public:
		Sum &operator=(const Sum &sSrc) = delete;
		
	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpInput(const Node *pDy);
	};
}

#endif