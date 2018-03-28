
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_LRELULAYER_GPU_H

#define _CLASS_TINNET_LAYER_LRELULAYER_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../TinNet_GPU_Backend.h"
#include "../GPUVector.h"

#include "Layer_GPU.h"

#include <cstddef>

namespace TinNet::Layer
{
	class TINNET_DLL LReLULayer_GPU : public Layer_GPU
	{
	public:
		LReLULayer_GPU(std::size_t nFanIn);
		LReLULayer_GPU(const LReLULayer_GPU &sSrc) = default;
		~LReLULayer_GPU() = default;

	public:
		LReLULayer_GPU &operator=(const LReLULayer_GPU &sSrc) = default;

	public:
		virtual const char *name() const override;
		virtual void initBias(std::function<float()> sGenerator) override;
		virtual void initWeight(std::function<float()> sGenerator) override;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const override;
		virtual void forward(const GPUVector &sInput, GPUVector &sOutput) const override;
		virtual void forward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sInput, GPUVector &sOutput, bool bTrainingPhase) const override;
		virtual void backward(std::size_t nIndex, std::size_t nBatchSize, const GPUVector &sForwardInput, const GPUVector &sBackwardInput, GPUVector &sBackwardOutput, GPUVector &sBiasDelta, GPUVector &sWeightDelta) const override;
		virtual void update(const GPUVector &sBiasDelta, const GPUVector &sWeightDelta) override;
		virtual void update(float nFactor, const GPUVector &sBiasDelta, const GPUVector &sWeightDelta) override;
	};
}

#endif