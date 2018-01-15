
/*
	2018.01.14
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_TANHLAYER_H

#define _CLASS_CAYSNET_LAYER_TANHLAYER_H

#include "../CaysNetDLL.h"

#include "../Layer/Layer.h"
#include "../IO/Serializable.h"

#include <cmath>
#include <cstddef>
#include <memory>

namespace CaysNet::Layer
{
	class CAYSNET_DLL TanhLayer : public Layer
	{
	public:
		TanhLayer(std::size_t nFanIn);
		TanhLayer(const TanhLayer &sSrc);
		~TanhLayer() = default;
		
	public:
		TanhLayer &operator=(const TanhLayer &sSrc);
		
	public:
		virtual std::unique_ptr<Layer> duplicate() const override;
		virtual void initBias(std::function<float()> sGenerator) override;
		virtual void initWeight(std::function<float()> sGenerator) override;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const override;
		virtual void forward(const float *pInput, float *pOutput) const override;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput) const override;
		virtual void backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pWeightDelta) const override;
		virtual void update(const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void update(float nFactor, const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};
}

#endif