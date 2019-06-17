
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
#include <stdexcept>
#include <string_view>
#include <tuple>
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
		std::vector<bool> sReduceAxis;
		
	public:
		Sum(Core::Graph *pGraph, std::string_view sName, bool bSqueeze, const std::vector<bool> &sReduceAxis);
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