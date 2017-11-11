
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_REINFORCEMENT_MONTE_CARLO_POLICY_GRADIENT_H

#define _CLASS_CAYSNET_OPTIMIZER_REINFORCEMENT_MONTE_CARLO_POLICY_GRADIENT_H

#include "../../CaysNetDLL.h"

#include "../../Layer/Layer.h"
#include "../../NN.h"

#include "../../Loss/Losses.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer::Reinforcement
{
	class CAYSNET_DLL MonteCarloPolicyGradient final
	{
	private:
		float nLearningRate;
		std::vector<std::vector<float>> sOutput;
		std::vector<std::vector<float>> sBiasDelta;
		std::vector<std::vector<std::vector<float>>> sWeightDelta;
		NN &sNN;
		
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
		//double checkGradient(const float *pState, const float *pActionTaken, float nReward, std::size_t nLayerIndex, std::size_t nInputIndex, std::size_t nOutputIndex);
		void update(const float *pState, const float *pActionTaken, std::size_t nActionTakenIndex, float nReward);
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