
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_OPTIMIZERBASE_H

#define _CLASS_TINNET_OPTIMIZER_OPTIMIZERBASE_H

#include "../TinNetDLL.h"

#include "../Layer/Layer.h"
#include "../NN.h"
#include "OptimizerHelper.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL OptimizerBase
	{
	protected:
		NN &sNN;
		std::size_t nBatchSize;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<float>> sWeightDelta;
		std::vector<std::vector<float>> sBackwardInput;
		std::vector<std::vector<std::vector<float>>> sForwardOutput;
		std::vector<std::vector<std::vector<float>>> sBackwardOutput;
		std::mt19937_64 sEngine;
		
	public:
		OptimizerBase(NN &sNN, std::size_t nNewBatchSize);
		OptimizerBase(const OptimizerBase &sSrc) = delete;
		OptimizerBase(OptimizerBase &&sSrc);
		virtual ~OptimizerBase() = default;
		
	public:
		OptimizerBase &operator=(const OptimizerBase &sSrc) = delete;
		
	public:
		inline NN &network();
		inline const NN &network() const;
		inline std::size_t batchSize() const;
		template<class LossFunc> void train(std::size_t nEpoch, std::size_t nSize, std::vector<float> *pInput, std::vector<float> *pOutput);
		void computeGradient(std::size_t nSize, const std::vector<float> *pInput, const std::vector<float> *pOutput, std::function<const float *(std::size_t, std::vector<std::vector<float>> &, std::vector<std::vector<float>> &)> fBefore, std::function<void(std::size_t)> fAfter);
		virtual void applyGradient(std::size_t nActualBatchSize, float nGradientFactor) = 0;
	};

	inline NN &OptimizerBase::network()
	{
		return this->sNN;
	}

	inline const NN &OptimizerBase::network() const
	{
		return this->sNN;
	}

	inline std::size_t OptimizerBase::batchSize() const
	{
		return this->nBatchSize;
	}
}

#include "OptimizerBase.hpp"

#endif