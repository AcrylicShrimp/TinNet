
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_LAYER_H

#define _CLASS_CAYSNET_LAYER_LAYER_H

#include "../CaysNetDLL.h"

#include "../Activation/Activation.h"
#include "../Activation/Activations.h"
#include "../IO/Serializable.h"

#include <cassert>
#include <cstddef>
#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace CaysNet::Layer
{
	class CAYSNET_DLL Layer : public IO::Serializable
	{
	protected:
		Activation::Activation *pActivation;
		std::size_t nFanIn;
		std::size_t nFanOut;

	public:
		Layer(Activation::Activation *pNewActivation, std::size_t nFanIn, std::size_t nFanOut);
		Layer(const Layer &sSrc);
		Layer(Layer &&sSrc);
		virtual ~Layer();

	public:
		Layer &operator=(const Layer &sSrc);
		Layer &operator=(Layer &&sSrc);

	public:
		inline Activation::Activation *activation();
		inline const Activation::Activation *activation() const;
		inline std::size_t fanIn() const;
		inline std::size_t fanOut() const;
		
		virtual Layer *duplicate() const = 0;
		virtual void initBias(std::function<float()> sGenerator) = 0;
		virtual void initWeight(std::function<float()> sGenerator) = 0;
		virtual void specifySize(
			std::size_t &nActivationInputSize,
			std::size_t &nActivationOutputSize,
			std::size_t &nBiasDeltaSize,
			std::size_t &nWeightDeltaSize) const = 0;
		virtual void forward(const float *pInput, float *pOutput) const = 0;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput) const = 0;
		virtual void forward(
			std::size_t nBatchSize,
			const std::vector<float> *pInput,
			std::vector<float> *pOutput,
			std::vector<float> *pActivationInput,
			std::vector<float> *pActivationOutput) const = 0;
		virtual void backward(
			std::size_t nBatchSize,
			const std::vector<float> *pActivationInput,
			const std::vector<float> *pActivationOutput,
			const std::vector<float> *pForwardInput,
			const std::vector<float> *pBackwardInput,
			std::vector<float> *pBackwardOutput,
			float *pBiasDelta,
			float *pWeightDelta,
			float *pBiasDeltaBuffer,
			float *pWeightDeltaBuffer) const = 0;
		virtual void update(float nFactor, const float *pBiasDelta, const float *pWeightDelta) = 0;
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};

	inline Activation::Activation *Layer::activation()
	{
		return this->pActivation;
	}

	inline const Activation::Activation *Layer::activation() const
	{
		return this->pActivation;
	}

	inline std::size_t Layer::fanIn() const
	{
		return this->nFanIn;
	}

	inline std::size_t Layer::fanOut() const
	{
		return this->nFanOut;
	}
}

#endif