
/*
	2019.03.31
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_SUM_H

#define _CLASS_TINNET_NODE_SUM_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"
#include "../Core/Memory.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace TinNet::Node
{
	class TINNET_DLL Sum : public Node
	{
		TINNET_NODE_TYPE_DCL(Sum)

	public:
		const bool bSqueeze;

	protected:
		NodeInput sInput;
		NodeInput sInputAxis;
		
	public:
		Sum(Core::Graph *pGraph, std::string_view sName, bool bSqueeze);
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