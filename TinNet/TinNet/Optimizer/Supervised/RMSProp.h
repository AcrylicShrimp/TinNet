
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SUPERVISED_RMSPROP_H

#define _CLASS_TINNET_OPTIMIZER_SUPERVISED_RMSPROP_H

#include "../../TinNetDLL.h"

#include "../../NN.h"
#include "SupervisedOptimizerBase.h"

#include <cstddef>
#include <utility>
#include <vector>

namespace TinNet::Optimizer::Supervised
{
	class TINNET_DLL RMSProp : public SupervisedOptimizerBase
	{
	private:
		float nDecay;
		float nLearningRate;
		std::vector<std::vector<float>> sBiasRate;
		std::vector<std::vector<float>> sWeightRate;
		
	public:
		RMSProp(NN &sNN, std::size_t nNewBatchSize, float nNewDecay, float nNewLearningRate);
		RMSProp(const RMSProp &sSrc) = delete;
		RMSProp(RMSProp &&sSrc);
		~RMSProp() = default;
		
	public:
		RMSProp &operator=(const RMSProp &sSrc) = delete;
		
	public:
		inline float &decay();
		inline float decay() const;
		inline float &learningRate();
		inline float learningRate() const;

	protected:
		virtual void applyGradient(std::size_t nActualBatchSize) override;
	};

	inline float &RMSProp::decay()
	{
		return this->nDecay;
	}

	inline float RMSProp::decay() const
	{
		return this->nDecay;
	}

	inline float &RMSProp::learningRate()
	{
		return this->nLearningRate;
	}

	inline float RMSProp::learningRate() const
	{
		return this->nLearningRate;
	}
}

#endif