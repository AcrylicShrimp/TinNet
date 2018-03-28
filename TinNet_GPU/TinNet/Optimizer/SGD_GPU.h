
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_SGD_GPU_H

#define _CLASS_TINNET_OPTIMIZER_SGD_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../NN_GPU.h"
#include "OptimizerBase_GPU.h"

namespace TinNet::Optimizer
{
	class TINNET_DLL SGD_GPU : public OptimizerBase_GPU
	{
	protected:
		float nLearningRate;
		
	public:
		SGD_GPU(NN_GPU &sNN, std::size_t nNewBatchSize, float nNewLearningRate);
		SGD_GPU(const SGD_GPU &sSrc) = delete;
		~SGD_GPU() = default;
		
	public:
		SGD_GPU &operator=(const SGD_GPU &sSrc) = delete;
		
	public:
		inline float &learningRate();
		inline float learningRate() const;

	protected:
		virtual void applyGradient(std::size_t nActualBatchSize, float nGradientFactor) override;
	};

	inline float &SGD_GPU::learningRate()
	{
		return this->nLearningRate;
	}

	inline float SGD_GPU::learningRate() const
	{
		return this->nLearningRate;
	}
}

#endif