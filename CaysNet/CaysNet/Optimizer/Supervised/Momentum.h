
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
		float nMomentumTerm;
		float nLearningRate;
		NN &sNN;
		std::vector<std::vector<float>> sActivationInput;
		std::vector<std::vector<float>> sActivationOutput;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<float>> sWeightDelta;
		std::vector<std::vector<float>> sBiasMomentum;
		std::vector<std::vector<float>> sWeightMomentum;
		std::vector<std::vector<float>> sBiasDeltaBuffer;
		std::vector<std::vector<float>> sWeightDeltaBuffer;
		std::vector<std::vector<float>> sBackward;
		std::mt19937_64 sEngine;
		
	public:
		Momentum(NN &sNN, float nNewMomentumTerm, float nNewLearningRate);
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
		template<class LossFunc> void train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch);
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