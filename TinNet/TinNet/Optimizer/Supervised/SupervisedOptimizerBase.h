
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SUPERVISED_SUPERVISEDOPTIMIZERBASE_H

#define _CLASS_TINNET_OPTIMIZER_SUPERVISED_SUPERVISEDOPTIMIZERBASE_H

#include "../../TinNetDLL.h"

#include "../../Layer/Layer.h"
#include "../../NN.h"
#include "../OptimizerHelper.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace TinNet::Optimizer::Supervised
{
	class TINNET_DLL SupervisedOptimizerBase
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
		SupervisedOptimizerBase(NN &sNN, std::size_t nNewBatchSize);
		SupervisedOptimizerBase(const SupervisedOptimizerBase &sSrc) = delete;
		SupervisedOptimizerBase(SupervisedOptimizerBase &&sSrc);
		virtual ~SupervisedOptimizerBase() = default;
		
	public:
		SupervisedOptimizerBase &operator=(const SupervisedOptimizerBase &sSrc) = delete;
		
	public:
		template<class LossFunc> void train(std::size_t nEpoch, std::size_t nSize, std::vector<float> *pInput, std::vector<float> *pOutput);

	protected:
		virtual void applyGradient(std::size_t nActualBatchSize) = 0;
	};
}

#include "SupervisedOptimizerBase.hpp"

#endif