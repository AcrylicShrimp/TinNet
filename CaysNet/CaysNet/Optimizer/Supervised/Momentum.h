
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_MOMENTUM_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_MOMENTUM_H

#include "../../CaysNetDLL.h"

#include "../../NN.h"
#include "SupervisedOptimizerBase.h"

#include <cstddef>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer::Supervised
{
	class CAYSNET_DLL Momentum : public SupervisedOptimizerBase
	{
	protected:
		float nMomentumTerm;
		float nLearningRate;
		std::vector<std::vector<float>> sBiasMomentum;
		std::vector<std::vector<float>> sWeightMomentum;
		
	public:
		Momentum(NN &sNN, std::size_t nNewBatchSize, float nNewMomentumTerm, float nNewLearningRate);
		Momentum(const Momentum &sSrc) = delete;
		Momentum(Momentum &&sSrc);
		~Momentum() = default;
		
	public:
		Momentum &operator=(const Momentum &sSrc) = delete;
		
	public:
		inline float &momentumTerm();
		inline float momentumTerm() const;
		inline float &learningRate();
		inline float learningRate() const;

	protected:
		virtual void applyGradient(std::size_t nActualBatchSize) override;
	};

	inline float &Momentum::momentumTerm()
	{
		return this->nMomentumTerm;
	}

	inline float Momentum::momentumTerm() const
	{
		return this->nMomentumTerm;
	}

	inline float &Momentum::learningRate()
	{
		return this->nLearningRate;
	}

	inline float Momentum::learningRate() const
	{
		return this->nLearningRate;
	}
}

#endif