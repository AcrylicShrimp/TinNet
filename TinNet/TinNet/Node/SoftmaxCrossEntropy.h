
/*
	2019.07.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_SOFTMAXCROSSENTROPY_H

#define _CLASS_TINNET_NODE_SOFTMAXCROSSENTROPY_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"

#include "Node.h"
#include "NodeInput.h"

#include <cmath>
#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL SoftmaxCrossEntropy : public Node
	{
		TINNET_NODE_TYPE_DCL(SoftmaxCrossEntropy)

	protected:
		NodeInput sInputLabel;
		NodeInput sInputProb;
		
	public:
		SoftmaxCrossEntropy(Core::Graph *pGraph, std::string_view sName);
		SoftmaxCrossEntropy(const SoftmaxCrossEntropy &sSrc) = delete;
		virtual ~SoftmaxCrossEntropy() noexcept = default;
		
	public:
		SoftmaxCrossEntropy &operator=(const SoftmaxCrossEntropy &sSrc) = delete;
		
	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpLabel(const Node *pDy);
		void __backwardOpProb(const Node *pDy);
	};
}

#endif