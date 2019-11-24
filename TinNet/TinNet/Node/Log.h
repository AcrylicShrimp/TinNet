
/*
	2019.07.31
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_LOG_H

#define _CLASS_TINNET_NODE_LOG_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Log : public Node
	{
		TINNET_NODE_TYPE_DCL(Log)

	protected:
		NodeInput sInput;
		
	public:
		Log(Core::Graph *pGraph, std::string_view sName);
		Log(const Log &sSrc) = delete;
		virtual ~Log() noexcept = default;
		
	public:
		Log &operator=(const Log &sSrc) = delete;
		
	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOp(const Node *pDy);
	};
}

#endif