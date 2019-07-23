
/*
	2019.06.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_SOFTMAX_H

#define _CLASS_TINNET_NODE_SOFTMAX_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"
#include "../Core/Memory.h"

#include "Node.h"
#include "NodeInput.h"

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <vector>

namespace TinNet::Node
{
	class TINNET_DLL Softmax : public Node
	{
		TINNET_NODE_TYPE_DCL(Softmax)

	public:
		const std::vector<bool> sGroupAxis;

	protected:
		Core::Memory<float> sSummation;
		Core::Memory<float> sSummationGradient;
		NodeInput sInputLogit;
		std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> sIndexFactorList;

	public:
		Softmax(Core::Graph *pGraph, std::string_view sName, const std::vector<bool> &sGroupAxis);
		Softmax(const Softmax &sSrc) = delete;
		virtual ~Softmax() noexcept = default;
		
	public:
		Softmax &operator=(const Softmax &sSrc) = delete;
		
	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOp(const Node *pDy);
	};
}

#endif