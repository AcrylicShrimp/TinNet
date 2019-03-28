
/*
	2019.03.11
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_MM_H

#define _CLASS_TINNET_NODE_MM_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"
#include "../Core/Shape.h"
#include "../Core/Span.h"

#include "../Compute/GEMM.h"

#include "Node.h"
#include "NodeInput.h"

#include <stdexcept>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL MM : public Node
	{
		TINNET_NODE_TYPE_DCL(MM)

	protected:
		NodeInput sInputLeft;
		NodeInput sInputRight;

	public:
		MM(Core::Graph *pGraph, std::string_view sName);
		MM(const MM &sSrc) = delete;
		virtual ~MM() noexcept = default;
		
	public:
		MM &operator=(const MM &sSrc) = delete;
		
	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpLeft(const Node *pDy);
		void __backwardOpRight(const Node *pDy);
	};
}

#endif