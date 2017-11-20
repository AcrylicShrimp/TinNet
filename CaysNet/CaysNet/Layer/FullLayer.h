
/*
	2017.11.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_FULL_LAYER_H

#define _CLASS_CAYSNET_LAYER_FULL_LAYER_H

#include "../CaysNetDLL.h"

#include "../Layer/Layer.h"
#include "../IO/Serializable.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace CaysNet::Layer
{
	class CAYSNET_DLL FullLayer final : public Layer
	{
	protected:
		std::vector<std::vector<float>> sWeight;
		std::vector<float> sBias;
		
	private:
		FullLayer(Activation::Activation *pActivation, std::size_t nFanIn, std::size_t nFanOut);
		FullLayer(const FullLayer &sSrc);
		FullLayer(FullLayer &&sSrc);
		~FullLayer() = default;
		
	public:
		FullLayer &operator=(const FullLayer &sSrc);
		FullLayer &operator=(FullLayer &&sSrc);
		
	public:
		virtual Layer *duplicate() const override;
		virtual void initBias(std::function<float()> sGenerator) override;
		virtual void initWeight(std::function<float()> sGenerator) override;
		virtual void specifySize(std::size_t &nActivationInputSize, std::size_t &nActivationOutputSize, std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const override;
		virtual void forward(const float *pInput, float *pOutput) const override;
		virtual void forward(const float *pInput, float *pOutput, float *pActivationInput, float *pActivationOutput) const override;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput) const override;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, std::vector<float> *pActivationInput, std::vector<float> *pActivationOutput) const override;
		virtual void backward(const float *pActivationInput, const float *pActivationOutput, const float *pForwardInput, const float *pBackwardInput, float *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const override;
		virtual void backward(std::size_t nBatchSize, const std::vector<float> *pActivationInput, const std::vector<float> *pActivationOutput, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta, float *pBiasDeltaBuffer) const override;
		virtual void update(const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void update(float nFactor, const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;

		template<class Activation, class ...ActivationConstructorParam> inline static FullLayer *make(std::size_t nFanIn, std::size_t nFanOut, ActivationConstructorParam && ...sParam);
	};

	template<class Activation, class ...ActivationConstructorParam> inline FullLayer *FullLayer::make(std::size_t nFanIn, std::size_t nFanOut, ActivationConstructorParam && ...sParam)
	{
		return new FullLayer(new Activation(std::forward<ActivationConstructorParam>(sParam)...), nFanIn, nFanOut);
	}
}

#endif