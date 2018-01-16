
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SUPERVISED_ADAM_H

#define _CLASS_TINNET_OPTIMIZER_SUPERVISED_ADAM_H

#include "../../TinNetDLL.h"

#include "../../NN.h"
#include "SupervisedOptimizerBase.h"

#include <cmath>
#include <cstddef>
#include <utility>
#include <vector>

namespace TinNet::Optimizer::Supervised
{
	class TINNET_DLL Adam : public SupervisedOptimizerBase
	{
	private:
		float nLearningRate;
		float nBeta1;
		float nBeta2;
		std::vector<std::vector<float>> sBiasBeta1;
		std::vector<std::vector<float>> sWeightBeta1;
		std::vector<std::vector<float>> sBiasBeta2;
		std::vector<std::vector<float>> sWeightBeta2;
		
	public:
		Adam(NN &sNN, std::size_t nNewBatchSize, float nNewLearningRate, float nNewBeta1, float nNewBeta2);
		Adam(const Adam &sSrc) = delete;
		Adam(Adam &&sSrc);
		~Adam() = default;
		
	public:
		Adam &operator=(const Adam &sSrc) = delete;
		
	public:
		inline float &learningRate();
		inline float learningRate() const;
		inline float &beta1();
		inline float beta1() const;
		inline float &beta2();
		inline float beta2() const;

	protected:
		virtual void applyGradient(std::size_t nActualBatchSize) override;
	};

	inline float &Adam::learningRate()
	{
		return this->nLearningRate;
	}

	inline float Adam::learningRate() const
	{
		return this->nLearningRate;
	}

	inline float &Adam::beta1()
	{
		return this->nBeta1;
	}

	inline float Adam::beta1() const
	{
		return this->nBeta1;
	}

	inline float &Adam::beta2()
	{
		return this->nBeta2;
	}

	inline float Adam::beta2() const
	{
		return this->nBeta2;
	}
}

#endif