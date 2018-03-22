
/*
	2017.11.14
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_ADAGRAD_H

#define _CLASS_TINNET_OPTIMIZER_ADAGRAD_H

#include "../TinNetDLL.h"

#include "../NN.h"
#include "OptimizerBase.h"

#include <cstddef>
#include <utility>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL Adagrad : public OptimizerBase
	{
	private:
		float nLearningRate;
		std::vector<std::vector<float>> sBiasRate;
		std::vector<std::vector<float>> sWeightRate;

	public:
		Adagrad(NN &sNN, std::size_t nNewBatchSize, float nNewLearningRate);
		Adagrad(const Adagrad &sSrc) = delete;
		Adagrad(Adagrad &&sSrc);
		~Adagrad() = default;

	public:
		Adagrad &operator=(const Adagrad &sSrc) = delete;

	public:
		inline float &learningRate();
		inline float learningRate() const;
		virtual void applyGradient(std::size_t nActualBatchSize, float nGradientFactor) override;
	};

	inline float &Adagrad::learningRate()
	{
		return this->nLearningRate;
	}

	inline float Adagrad::learningRate() const
	{
		return this->nLearningRate;
	}
}

#endif