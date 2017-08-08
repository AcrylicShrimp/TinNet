
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SGD_H

#define _CLASS_CAYSNET_OPTIMIZER_SGD_H

#include "Layer.h"
#include "NN.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer
{
	template<class LossFunc> class SGD
	{
	private:
		float nLearningRate;
		NN<LossFunc> &sNN;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<std::vector<float>>> sWeightDelta;
		std::mt19937_64 sEngine;

	public:
		SGD(NN<LossFunc> &sNN, float nNewLearningRate);
		SGD(const SGD &sSrc) = delete;
		SGD(SGD &&sSrc);
		~SGD() = default;

	public:
		SGD &operator=(const SGD &sSrc) = delete;
		SGD &operator=(SGD &&sSrc) = delete;

	public:
		inline float &learningRate();
		inline float learningRate() const;
		void train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch);
	};

	template<class LossFunc> inline float &SGD<LossFunc>::learningRate()
	{
		return this->nLearningRate;
	}

	template<class LossFunc> inline float SGD<LossFunc>::learningRate() const
	{
		return this->nLearningRate;
	}
}

#include "SGD.hpp"

#endif