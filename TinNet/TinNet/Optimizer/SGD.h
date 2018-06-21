
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SGD_H

#define _CLASS_TINNET_OPTIMIZER_SGD_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "OptimizerBase.h"

namespace TinNet::Optimizer
{
	class TINNET_DLL SGD final : public OptimizerBase
	{
	public:
		SGD(Graph &sGraph);
		SGD(const SGD &sSrc) = default;
		SGD(SGD &&sSrc) = default;
		~SGD() = default;
		
	public:
		SGD &operator=(const SGD &sSrc) = default;
		SGD &operator=(SGD &&sSrc) = default;
		
	protected:
		virtual void applyGradient(float nLearningRate) override;
	};
}

#endif