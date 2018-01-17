
/*
	2018.01.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_CONVLAYER_H

#define _CLASS_TINNET_LAYER_CONVLAYER_H

#include "../TinNetDLL.h"

#include "../Layer/Layer.h"
#include "../IO/Serializable.h"

#include <cstddef>
#include <future>
#include <utility>
#include <vector>

namespace TinNet::Layer
{
	class TINNET_DLL ConvLayer : public Layer
	{
	protected:
		std::size_t nWidth;
		std::size_t nHeight;
		std::size_t nChannel;
		std::size_t nFilter;
		std::size_t nFilterWidth;
		std::size_t nFilterHeight;
		std::size_t nStrideHorizontal;
		std::size_t nStrideVertical;
		std::size_t nOutputWidth;
		std::size_t nOutputHeight;
		std::size_t nZeroPaddingHorizontalNegative;
		std::size_t nZeroPaddingHorizontalPositive;
		std::size_t nZeroPaddingVerticalNegative;
		std::size_t nZeroPaddingVerticalPositive;
		std::vector<float> sBias;
		std::vector<std::vector<std::vector<float>>> sWeight;
		mutable std::vector<std::future<void>> sFuture;
		
	public:
		ConvLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
				  std::size_t nNewFilterWidth,
				  std::size_t nNewFilterHeight);
		ConvLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
				  std::size_t nNewFilterWidth,
				  std::size_t nNewFilterHeight,
				  std::size_t nNewStrideHorizontal,
				  std::size_t nNewStrideVertical);
		ConvLayer(std::size_t nNewWidth, std::size_t nNewHeight, std::size_t nNewChannel, std::size_t nNewFilter,
				  std::size_t nNewFilterWidth,
				  std::size_t nNewFilterHeight,
				  std::size_t nNewStrideHorizontal,
				  std::size_t nNewStrideVertical,
				  std::size_t nNewOutputWidth,
				  std::size_t nNewOutputHeight);
		ConvLayer(const ConvLayer &sSrc) = delete;
		ConvLayer(ConvLayer &&sSrc);
		~ConvLayer() = default;
		
	public:
		ConvLayer &operator=(const ConvLayer &sSrc) = delete;
		ConvLayer &operator=(ConvLayer &&sSrc);
		
	public:
		inline std::size_t width() const;
		inline std::size_t height() const;
		inline std::size_t channel() const;
		inline std::size_t filter() const;
		inline std::size_t filterWidth() const;
		inline std::size_t filterHeight() const;
		inline std::size_t strideHorizontal() const;
		inline std::size_t strideVertical() const;
		inline std::size_t outputWidth() const;
		inline std::size_t outputHeight() const;
		inline std::size_t zeroPaddingHorizontalNegative() const;
		inline std::size_t zeroPaddingHorizontalPositive() const;
		inline std::size_t zeroPaddingVerticalNegative() const;
		inline std::size_t zeroPaddingVerticalPositive() const;
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

	inline std::size_t ConvLayer::width() const
	{
		return this->nWidth;
	}

	inline std::size_t ConvLayer::height() const
	{
		return this->nHeight;
	}

	inline std::size_t ConvLayer::channel() const
	{
		return this->nChannel;
	}

	inline std::size_t ConvLayer::filter() const
	{
		return this->nFilter;
	}

	inline std::size_t ConvLayer::filterWidth() const
	{
		return this->nFilterWidth;
	}

	inline std::size_t ConvLayer::filterHeight() const
	{
		return this->nFilterHeight;
	}

	inline std::size_t ConvLayer::strideHorizontal() const
	{
		return this->nStrideHorizontal;
	}

	inline std::size_t ConvLayer::strideVertical() const
	{
		return this->nStrideVertical;
	}

	inline std::size_t ConvLayer::outputWidth() const
	{
		return this->nOutputWidth;
	}

	inline std::size_t ConvLayer::outputHeight() const
	{
		return this->nOutputHeight;
	}

	inline std::size_t ConvLayer::zeroPaddingHorizontalNegative() const
	{
		return this->nZeroPaddingHorizontalNegative;
	}

	inline std::size_t ConvLayer::zeroPaddingHorizontalPositive() const
	{
		return this->nZeroPaddingHorizontalPositive;
	}

	inline std::size_t ConvLayer::zeroPaddingVerticalNegative() const
	{
		return this->nZeroPaddingVerticalNegative;
	}

	inline std::size_t ConvLayer::zeroPaddingVerticalPositive() const
	{
		return this->nZeroPaddingVerticalPositive;
	}
}

#endif