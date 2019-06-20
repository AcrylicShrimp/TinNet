
/*
	2019.06.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_MEAN_H

#define _CLASS_TINNET_NODE_MEAN_H

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
	class TINNET_DLL Mean : public Node
	{
		TINNET_NODE_TYPE_DCL(Mean)

	public:
		const bool bSqueeze;
		const std::vector<bool> sReduceAxis;

	protected:
		NodeInput sInput;
		float nMeanFactor;
		std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> sIndexFactorList;
		
	public:
		Mean(Core::Graph *pGraph, std::string_view sName, bool bSqueeze, const std::vector<bool> &sReduceAxis);
		Mean(const Mean &sSrc) = delete;
		virtual ~Mean() noexcept = default;
		
	public:
		Mean &operator=(const Mean &sSrc) = delete;
		
	public:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpInput(const Node *pDy);
	};
}

#endif