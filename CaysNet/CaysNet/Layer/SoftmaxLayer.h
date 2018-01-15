
/*
	2018.01.14
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_SOFTMAXLAYER_H

#define _CLASS_CAYSNET_LAYER_SOFTMAXLAYER_H

#include "../CaysNetDLL.h"

#include "../Layer/Layer.h"
#include "../IO/Serializable.h"

#include <cmath>
#include <cstddef>
#include <memory>
#include <utility>

namespace CaysNet::Layer
{
	class CAYSNET_DLL SoftmaxLayer : public Layer
	{
	private:
		mutable std::vector<float> sOutput;

	public:
		SoftmaxLayer(std::size_t nFanIn);
		SoftmaxLayer(const SoftmaxLayer &sSrc);
		SoftmaxLayer(SoftmaxLayer &&sSrc);
		~SoftmaxLayer() = default;
		
	public:
		SoftmaxLayer &operator=(const SoftmaxLayer &sSrc);
		SoftmaxLayer &operator=(SoftmaxLayer &&sSrc);
		
	public:
		virtual const char *name() const override;
		virtual std::unique_ptr<Layer> duplicate() const override;
		virtual void initBias(std::function<float()> sGenerator) override;
		virtual void initWeight(std::function<float()> sGenerator) override;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const override;
		virtual void forward(const float *pInput, float *pOutput) const override;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase = false) const override;
		virtual void backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pWeightDelta) const override;
		virtual void update(const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void update(float nFactor, const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void deserialize(std::ifstream &sInput) override;
	};
}

#endif