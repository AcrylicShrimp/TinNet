
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_SGD_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_SGD_H

#include "../../Layer.h"
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
	class SGD final
	{
	private:
		float nLearningRate;
		NN &sNN;
		std::vector<std::vector<float>> sOutput;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<std::vector<float>>> sWeightDelta;
		std::mt19937_64 sEngine;

	public:
		SGD(NN &sNN, float nNewLearningRate);
		SGD(const SGD &sSrc) = delete;
		SGD(SGD &&sSrc);
		~SGD() = default;

	public:
		SGD &operator=(const SGD &sSrc) = delete;
		SGD &operator=(SGD &&sSrc) = delete;

	public:
		inline float &learningRate();
		inline float learningRate() const;
		template<class LossFunc> std::pair<float, float> calcNumericalGradient(const std::vector<float> &sInput, const std::vector<float> &sOutput, std::size_t nLayerIndex, std::size_t nInputIndex, std::size_t nOutputIndex);
		template<class LossFunc> void train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch);
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

#include "SGD.hpp"

#endif