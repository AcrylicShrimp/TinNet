
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_SGD_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_SGD_H

#include "../../CaysNetDLL.h"

#include "../../NN.h"
#include "SupervisedOptimizerBase.h"

#include <cstddef>
#include <utility>
#include <vector>

namespace CaysNet::Optimizer::Supervised
{
	class CAYSNET_DLL SGD : public SupervisedOptimizerBase
	{
	protected:
		float nLearningRate;

	public:
		SGD(NN &sNN, std::size_t nNewBatchSize, float nNewLearningRate);
		SGD(const SGD &sSrc) = delete;
		SGD(SGD &&sSrc);
		~SGD() = default;

	public:
		SGD &operator=(const SGD &sSrc) = delete;

	public:
		inline float &learningRate();
		inline float learningRate() const;

	protected:
		virtual void applyGradient(std::size_t nActualBatchSize) override;
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

#endif