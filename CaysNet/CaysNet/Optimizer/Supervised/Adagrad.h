
/*
	2017.11.14
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_ADAGRAD_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_ADAGRAD_H

#include "../../CaysNetDLL.h"

#include "../../NN.h"
#include "SupervisedOptimizerBase.h"

#include <cstddef>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer::Supervised
{
	class CAYSNET_DLL Adagrad : public SupervisedOptimizerBase
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

	protected:
		virtual void applyGradient(std::size_t nActualBatchSize) override;
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