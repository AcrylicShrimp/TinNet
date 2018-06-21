
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_OPTIMIZERBASE_H

#define _CLASS_TINNET_OPTIMIZER_OPTIMIZERBASE_H

#include "../TinNetDLL.h"

#include "../Graph.h"
#include "../Initializable.h"

#include <cstddef>

namespace TinNet::Optimizer
{
	using Gradient = std::vector<std::vector<std::vector<float>>>;

	class TINNET_DLL OptimizerBase
	{
	protected:
		Graph &sGraph;
		std::vector<InitializablePtr> sInitializableList;
		Gradient sGradient;
		
	public:
		OptimizerBase(Graph &sGraph);
		OptimizerBase(const OptimizerBase &sSrc) = default;
		OptimizerBase(OptimizerBase &&sSrc) = default;
		virtual ~OptimizerBase() = default;
		
	public:
		OptimizerBase &operator=(const OptimizerBase &sSrc) = default;
		OptimizerBase &operator=(OptimizerBase &&sSrc) = default;
		
	public:
		void optimize(float nLearningRate);

	protected:
		void copyGradient(Gradient &sGradient, float nFactor = 1.f);
		void accumulateGradient(Gradient &sGradient, float nFactor = 1.f);
		void applyGradient(float nLearningRate, Gradient &sGradient);
		Gradient generateGradientBuffer();
		virtual void applyGradient(float nLearningRate) = 0;
	};
}

#endif