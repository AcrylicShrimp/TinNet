
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_SWISHLAYER_H

#define _CLASS_TINNET_LAYER_SWISHLAYER_H

#include "../TinNetDLL.h"

#include "../Layer/Layer.h"
#include "../IO/Serializable.h"

#include <cstddef>
#include <memory>

namespace TinNet::Layer
{
	class TINNET_DLL SwishLayer : public Layer
	{
	protected:
		float nBeta;
		
	public:
		SwishLayer(std::size_t nFanIn, float nBeta = 1.f);
		SwishLayer(const SwishLayer &sSrc);
		~SwishLayer() = default;
		
	public:
		SwishLayer &operator=(const SwishLayer &sSrc);
		
	public:
		virtual const char *name() const override;
		virtual std::unique_ptr<Layer> duplicate() const override;
		virtual void initBias(std::function<float()> sGenerator) override;
		virtual void initWeight(std::function<float()> sGenerator) override;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const override;
		virtual void forward(const float *pInput, float *pOutput) const override;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase = false) const override;
		virtual void backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const override;
		virtual void backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta, const float *pFactor) const override;
		virtual void update(const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void update(float nFactor, const float *pBiasDelta, const float *pWeightDelta) override;
	};
}

#endif