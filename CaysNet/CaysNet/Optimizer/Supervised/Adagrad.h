
/*
	2017.11.14
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_ADAGRAD_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_ADAGRAD_H

#include "../../CaysNetDLL.h"

#include "../../Layer/Layer.h"
#include "../../NN.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer::Supervised
{
	class CAYSNET_DLL Adagrad final
	{
	private:
		float nLearningRate;
		NN &sNN;
		std::vector<std::vector<float>> sActivationInput;
		std::vector<std::vector<float>> sActivationOutput;
		std::vector<std::vector<float>> sBiasRate;
		std::vector<std::vector<float>> sWeightRate;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<float>> sWeightDelta;
		std::vector<std::vector<float>> sBiasDeltaBuffer;
		std::vector<std::vector<float>> sWeightDeltaBuffer;
		std::vector<std::vector<float>> sBackward;
		std::mt19937_64 sEngine;

	public:
		Adagrad(NN &sNN, float nNewLearningRate);
		Adagrad(const Adagrad &sSrc) = delete;
		Adagrad(Adagrad &&sSrc);
		~Adagrad() = default;

	public:
		Adagrad &operator=(const Adagrad &sSrc) = delete;
		Adagrad &operator=(Adagrad &&sSrc) = delete;

	public:
		inline float &learningRate();
		inline float learningRate() const;
		template<class LossFunc> void train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch);
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

#include "Adagrad.hpp"

#endif