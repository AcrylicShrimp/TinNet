
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_MONTE_CARLO_POLICY_GRADIENT_H

#define _CLASS_TINNET_OPTIMIZER_MONTE_CARLO_POLICY_GRADIENT_H

#include "../TinNetDLL.h"

#include "../Loss/Losses.h"
#include "OptimizerBase.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL MonteCarloPolicyGradient final
	{
	private:
		OptimizerBase &sOptimizerBase;
		std::vector<float> sBackwardInput;
		std::mt19937_64 sEngine;
		
	public:
		MonteCarloPolicyGradient(OptimizerBase &sOptimizerBase);
		MonteCarloPolicyGradient(const MonteCarloPolicyGradient &sSrc) = delete;
		MonteCarloPolicyGradient(MonteCarloPolicyGradient &&sSrc);
		~MonteCarloPolicyGradient() = default;
		
	public:
		MonteCarloPolicyGradient &operator=(const MonteCarloPolicyGradient &sSrc) = delete;
		MonteCarloPolicyGradient &operator=(MonteCarloPolicyGradient &&sSrc) = delete;
		
	public:
		inline OptimizerBase &optimizerBase();
		inline const OptimizerBase &optimizerBase() const;
		void update(std::size_t nSize, std::vector<float> *pState, std::vector<float> *pActionTaken, float *pReward);
	};

	inline OptimizerBase &MonteCarloPolicyGradient::optimizerBase()
	{
		return this->sOptimizerBase;
	}

	inline const OptimizerBase &MonteCarloPolicyGradient::optimizerBase() const
	{
		return this->sOptimizerBase;
	}
}

#endif