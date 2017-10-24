
/*
	2017.10.24
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_NAG_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_NAG_H

#include "../../CaysNetDLL.h"

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
	class CAYSNET_DLL NAG final
	{
	private:
		float nMomentumTerm;
		float nLearningRate;
		NN &sNN;
		std::vector<std::vector<float>> sOutput;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<float>> sBiasMomentum;
		std::vector<std::vector<std::vector<float>>> sWeightDelta;
		std::vector<std::vector<std::vector<float>>> sWeightMomentum;
		std::mt19937_64 sEngine;
		
	public:
		NAG(NN &sNN, float nNewMomentumTerm, float nNewLearningRate);
		NAG(const NAG &sSrc) = delete;
		NAG(NAG &&sSrc);
		~NAG() = default;
		
	public:
		NAG &operator=(const NAG &sSrc) = delete;
		NAG &operator=(NAG &&sSrc) = delete;
		
	public:
		inline float &momentumTerm();
		inline float momentumTerm() const;
		inline float &learningRate();
		inline float learningRate() const;
		template<class LossFunc> void train(std::vector<std::vector<float>> &sInput, std::vector<std::vector<float>> &sOutput, std::size_t nBatchSize, std::size_t nEpoch);
	};

	inline float &NAG::momentumTerm()
	{
		return this->nMomentumTerm;
	}

	inline float NAG::momentumTerm() const
	{
		return this->nMomentumTerm;
	}

	inline float &NAG::learningRate()
	{
		return this->nLearningRate;
	}

	inline float NAG::learningRate() const
	{
		return this->nLearningRate;
	}
}

#include "NAG.hpp"

#endif