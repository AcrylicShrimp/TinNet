
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_SWISHLAYER_GPU_H

#define _CLASS_TINNET_LAYER_SWISHLAYER_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../TinNet_GPU_Backend.h"
#include "../GPUVector.h"

#include "Layer_GPU.h"

#include <cstddef>

namespace TinNet::Layer
{
	class TINNET_DLL SwishLayer_GPU : public Layer_GPU
	{
	protected:
		float nBeta;

	public:
		SwishLayer_GPU(std::size_t nFanIn, float nBeta = 1.f);
		SwishLayer_GPU(const SwishLayer_GPU &sSrc) = delete;
		~SwishLayer_GPU() = default;

	public:
		SwishLayer_GPU &operator=(const SwishLayer_GPU &sSrc) = delete;

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