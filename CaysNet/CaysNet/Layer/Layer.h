
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_LAYER_H

#define _CLASS_CAYSNET_LAYER_LAYER_H

#include "../CaysNetDLL.h"

#include "../IO/Serializable.h"

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

namespace CaysNet::Layer
{
	class CAYSNET_DLL Layer : public IO::Serializable
	{
	protected:
		std::size_t nFanIn;
		std::size_t nFanOut;

	public:
		Layer(std::size_t nFanIn, std::size_t nFanOut);
		Layer(const Layer &sSrc);
		virtual ~Layer() = default;

	public:
		Layer &operator=(const Layer &sSrc);

	public:
		inline std::size_t fanIn() const;
		inline std::size_t fanOut() const;
		
		virtual std::unique_ptr<Layer> duplicate() const = 0;
		virtual void initBias(std::function<float()> sGenerator) = 0;
		virtual void initWeight(std::function<float()> sGenerator) = 0;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const = 0;
		virtual void forward(const float *pInput, float *pOutput) const = 0;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput) const = 0;
		virtual void backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pWeightDelta) const = 0;
		virtual void update(const float *pBiasDelta, const float *pWeightDelta) = 0;
		virtual void update(float nFactor, const float *pBiasDelta, const float *pWeightDelta) = 0;
	};

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