
/*
	2018.01.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_FULLLAYER_GPU_H

#define _CLASS_TINNET_LAYER_FULLLAYER_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../TinNet_GPU_Backend.h"
#include "../GPUVector.h"

#include "Layer_GPU.h"

#include <cstddef>

namespace TinNet::Layer
{
	class TINNET_DLL FullLayer_GPU : public Layer_GPU
	{
	protected:
		GPUVector sBias;
		GPUVector sWeight;

	public:
		FullLayer_GPU(std::size_t nFanIn, std::size_t nFanOut);
		FullLayer_GPU(const FullLayer_GPU &sSrc) = delete;
		~FullLayer_GPU() = default;

	public:
		FullLayer_GPU &operator=(const FullLayer_GPU &sSrc) = delete;

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