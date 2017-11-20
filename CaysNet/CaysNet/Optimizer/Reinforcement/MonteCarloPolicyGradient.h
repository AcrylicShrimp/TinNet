
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_REINFORCEMENT_MONTE_CARLO_POLICY_GRADIENT_H

#define _CLASS_CAYSNET_OPTIMIZER_REINFORCEMENT_MONTE_CARLO_POLICY_GRADIENT_H

#include "../../CaysNetDLL.h"

#include "../../Layer/Layer.h"
#include "../../NN.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer::Reinforcement
{
	class CAYSNET_DLL MonteCarloPolicyGradient final
	{
	private:
		NN &sNN;
		float nLearningRate;
		std::mt19937_64 sEngine;
		std::vector<std::vector<float>> sForwardOutput;
		std::vector<std::vector<float>> sBackwardOutput;
		std::vector<std::vector<float>> sActivationInput;
		std::vector<std::vector<float>> sActivationOutput;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<float>> sWeightDelta;
		std::vector<std::vector<float>> sBiasRate;
		std::vector<std::vector<float>> sWeightRate;
		
	public:
		MonteCarloPolicyGradient(NN &sNN, float nNewLearningRate);
		MonteCarloPolicyGradient(const MonteCarloPolicyGradient &sSrc) = delete;
		MonteCarloPolicyGradient(MonteCarloPolicyGradient &&sSrc);
		~MonteCarloPolicyGradient() = default;
		
	public:
		MonteCarloPolicyGradient &operator=(const MonteCarloPolicyGradient &sSrc) = delete;
		MonteCarloPolicyGradient &operator=(MonteCarloPolicyGradient &&sSrc) = delete;
		
	public:
		inline float &learningRate();
		inline float learningRate() const;
		void update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward);
	};

	inline float &MonteCarloPolicyGradient::learningRate()
	{
		return this->nLearningRate;
	}

	inline float MonteCarloPolicyGradient::learningRate() const
	{
		return this->nLearningRate;
	}
}

#endif