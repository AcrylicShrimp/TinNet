
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SGD_H

#define _CLASS_TINNET_OPTIMIZER_SGD_H

#include "../TinNetDLL.h"

#include "../NN.h"
#include "OptimizerBase.h"

#include <cstddef>
#include <utility>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL SGD : public OptimizerBase
	{
	protected:
		float nLearningRate;

	public:
		SGD(NN &sNN, std::size_t nNewBatchSize, float nNewLearningRate);
		SGD(const SGD &sSrc) = delete;
		SGD(SGD &&sSrc);
		~SGD() = default;

	public:
		SGD &operator=(const SGD &sSrc) = delete;

	public:
		inline float &learningRate();
		inline float learningRate() const;
		virtual void applyGradient(std::size_t nActualBatchSize, float nGradientFactor) override;
	};

	inline float &SGD::learningRate()
	{
		return this->nLearningRate;
	}

	inline float SGD::learningRate() const
	{
		return this->nLearningRate;
	}
}

#endif