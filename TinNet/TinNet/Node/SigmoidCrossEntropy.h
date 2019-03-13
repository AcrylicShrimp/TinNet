
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_SIGMOIDCROSSENTROPY_H

#define _CLASS_TINNET_NODE_SIGMOIDCROSSENTROPY_H

#include "../TinNetDLL.h"

#include "Node.h"
#include "NodeInput.h"

#include <cmath>
#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL SigmoidCrossEntropy : public Node
	{
	protected:
		NodeInput sInputLabel;
		NodeInput sInputProb;

	public:
		SigmoidCrossEntropy(std::string_view sName);
		SigmoidCrossEntropy(const SigmoidCrossEntropy &sSrc) = delete;
		virtual ~SigmoidCrossEntropy() noexcept = default;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpLabel(const Node *pDy);
		void __backwardOpProb(const Node *pDy);
	};
}

#endif