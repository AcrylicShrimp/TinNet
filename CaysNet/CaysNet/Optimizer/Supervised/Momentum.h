
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_MOMENTUM_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_MOMENTUM_H

#include "../../CaysNetDLL.h"

#include "../../Layer/Layer.h"
#include "../../NN.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer::Supervised
{
	class CAYSNET_DLL Momentum final
	{
	private:
		NN &sNN;
		std::size_t nBatchSize;
		float nMomentumTerm;
		float nLearningRate;
		std::mt19937_64 sEngine;
		std::vector<std::vector<std::vector<float>>> sForwardOutput;
		std::vector<std::vector<std::vector<float>>> sBackwardOutput;
		std::vector<std::vector<std::vector<float>>> sActivationInput;
		std::vector<std::vector<std::vector<float>>> sActivationOutput;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<float>> sWeightDelta;
		std::vector<std::vector<float>> sBiasMomentum;
		std::vector<std::vector<float>> sWeightMomentum;
		std::vector<std::vector<float>> sBiasDeltaBuffer;
		
	public:
		Momentum(NN &sNN, std::size_t nBatchSize, float nNewMomentumTerm, float nNewLearningRate);
		Momentum(const Momentum &sSrc) = delete;
		Momentum(Momentum &&sSrc);
		~Momentum() = default;
		
	public:
		Momentum &operator=(const Momentum &sSrc) = delete;
		Momentum &operator=(Momentum &&sSrc) = delete;
		
	public:
		inline float &momentumTerm();
		inline float momentumTerm() const;
		inline float &learningRate();
		inline float learningRate() const;
		template<class LossFunc> void train(std::size_t nEpoch, std::size_t nSize, std::vector<float> *pInput, std::vector<float> *pOutput);
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

#include "Momentum.hpp"

#endif