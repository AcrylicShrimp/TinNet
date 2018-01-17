
/*
	2018.01.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_MAXPOOLINGLAYER_H

#define _CLASS_TINNET_LAYER_MAXPOOLINGLAYER_H

#include "../TinNetDLL.h"

#include "../Layer/Layer.h"
#include "../IO/Serializable.h"

#include <algorithm>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>

namespace TinNet::Layer
{
	class TINNET_DLL MaxPoolingLayer : public Layer
	{
	protected:
		std::size_t nWidth;
		std::size_t nHeight;
		std::size_t nChannel;
		std::size_t nPoolingWidth;
		std::size_t nPoolingHeight;
		std::size_t nStrideHorizontal;
		std::size_t nStrideVertical;
		std::size_t nOutputWidth;
		std::size_t nOutputHeight;
		mutable std::vector<float> sMax;
		mutable std::vector<std::tuple<std::size_t, std::size_t>> sMaxPosition;
		
	public:
		MaxPoolingLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel,
						std::size_t nNewPoolingWidth,
						std::size_t nNewPoolingHeight);
		MaxPoolingLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel,
						std::size_t nNewPoolingWidth,
						std::size_t nNewPoolingHeight,
						std::size_t nStrideHorizontal,
						std::size_t nStrideVertical);
		MaxPoolingLayer(const MaxPoolingLayer &sSrc);
		MaxPoolingLayer(MaxPoolingLayer &&sSrc);
		~MaxPoolingLayer() = default;
		
	public:
		MaxPoolingLayer &operator=(const MaxPoolingLayer &sSrc);
		MaxPoolingLayer &operator=(MaxPoolingLayer &&sSrc);
		
	public:
		virtual const char *name() const override;
		virtual std::unique_ptr<Layer> duplicate() const override;
		virtual void initBias(std::function<float()> sGenerator) override;
		virtual void initWeight(std::function<float()> sGenerator) override;
		virtual void specifySize(std::size_t &nBiasDeltaSize, std::size_t &nWeightDeltaSize) const override;
		virtual void forward(const float *pInput, float *pOutput) const override;
		virtual void forward(std::size_t nBatchSize, const std::vector<float> *pInput, std::vector<float> *pOutput, bool bTrainingPhase = false) const override;
		virtual void backward(std::size_t nBatchSize, const std::vector<float> *pForwardInput, const std::vector<float> *pBackwardInput, std::vector<float> *pBackwardOutput, float *pBiasDelta, float *pWeightDelta) const override;
		virtual void update(const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void update(float nFactor, const float *pBiasDelta, const float *pWeightDelta) override;
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};
}

#endif