
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_ADAM_H

#define _CLASS_TINNET_OPTIMIZER_ADAM_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "OptimizerBase.h"

#include <cmath>
#include <initializer_list>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL Adam final : public OptimizerBase
	{
	protected:
		float nBeta1;
		float nBeta2;
		Gradient sGradientBeta1;
		Gradient sGradientBeta2;
		
	public:
		Adam(Graph &sGraph, float nBeta1, float nBeta2);
		Adam(Graph &sGraph, float nBeta1, float nBeta2, const std::vector<NodePtr> &sNodeList);
		Adam(const Adam &sSrc) = default;
		Adam(Adam &&sSrc) = default;
		~Adam() = default;
		
	public:
		Adam &operator=(const Adam &sSrc) = default;
		Adam &operator=(Adam &&sSrc) = default;
		
	protected:
		virtual void applyGradient(float nLearningRate) override;
	};
}

#endif