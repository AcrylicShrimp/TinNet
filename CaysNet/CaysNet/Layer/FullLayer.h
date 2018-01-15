
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
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace CaysNet::Layer
{
	class CAYSNET_DLL FullLayer final : public Layer
	{
	protected:
		std::vector<float> sBias;
		std::vector<std::vector<float>> sWeight;
		
	public:
		FullLayer(std::size_t nFanIn, std::size_t nFanOut);
		FullLayer(const FullLayer &sSrc);
		FullLayer(FullLayer &&sSrc);
		~FullLayer() = default;
		
	public:
		FullLayer &operator=(const FullLayer &sSrc);
		FullLayer &operator=(FullLayer &&sSrc);
		
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
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};
}

#endif