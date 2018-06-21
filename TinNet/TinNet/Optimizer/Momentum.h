
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_MOMENTUM_H

#define _CLASS_TINNET_OPTIMIZER_MOMENTUM_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "OptimizerBase.h"

namespace TinNet::Optimizer
{
	class TINNET_DLL Momentum final : public OptimizerBase
	{
	protected:
		float nMomentum;

	public:
		Momentum(Graph &sGraph, float nMomentum);
		Momentum(const Momentum &sSrc) = default;
		Momentum(Momentum &&sSrc) = default;
		~Momentum() = default;

	public:
		Momentum &operator=(const Momentum &sSrc) = default;
		Momentum &operator=(Momentum &&sSrc) = default;

	protected:
		virtual void applyGradient(float nLearningRate) override;
	};
}

#endif