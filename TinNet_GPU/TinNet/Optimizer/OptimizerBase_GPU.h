
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_OPTIMIZER_OPTIMIZERBASE_GPU_H

#define _CLASS_TINNET_OPTIMIZER_OPTIMIZERBASE_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../TinNet_GPU_Backend.h"
#include "../Layer/Layer_GPU.h"
#include "../NN_GPU.h"

#include "../GPUVector.h"

#include <algorithm>
#include <cstddef>
#include <vector>

namespace TinNet::Optimizer
{
	class TINNET_DLL OptimizerBase_GPU
	{
	protected:
		NN_GPU &sNN;
		std::size_t nBatchSize;
		std::vector<GPUVector> sBiasDelta;
		std::vector<GPUVector> sWeightDelta;
		GPUVector sBackwardInput;
		std::vector<GPUVector> sForwardOutput;
		std::vector<GPUVector> sBackwardOutput;

	public:
		OptimizerBase_GPU(NN_GPU &sNN, std::size_t nNewBatchSize);
		OptimizerBase_GPU(const OptimizerBase_GPU &sSrc) = delete;
		virtual ~OptimizerBase_GPU() = default;
		
	public:
		OptimizerBase_GPU &operator=(const OptimizerBase_GPU &sSrc) = delete;

	public:
		inline NN_GPU &network();
		inline const NN_GPU &network() const;
		inline std::size_t batchSize() const;
		template<class LossFunc> void train(std::size_t nEpoch, std::size_t nSize, GPUVector &sInput, GPUVector &sOutput);
		virtual void applyGradient(std::size_t nActualBatchSize, float nGradientFactor) = 0;
	};

	inline NN_GPU &OptimizerBase_GPU::network()
	{
		return this->sNN;
	}

	inline const NN_GPU &OptimizerBase_GPU::network() const
	{
		return this->sNN;
	}

	inline std::size_t OptimizerBase_GPU::batchSize() const
	{
		return this->nBatchSize;
	}
}

#include "OptimizerBase_GPU.hpp"

#endif