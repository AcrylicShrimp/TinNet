
/*
	2017.11.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_CONV_LAYER_H

#define _CLASS_CAYSNET_LAYER_CONV_LAYER_H

#include "../CaysNetDLL.h"

#include "../Layer/Layer.h"
#include "../IO/Serializable.h"

#include <cassert>
#include <cstddef>
#include <utility>

namespace CaysNet::Layer
{
	class CAYSNET_DLL ConvLayer final : public Layer
	{
	protected:
		std::vector<std::vector<float>> sWeight;
		std::vector<float> sBias;
		std::vector<float> sActivationInput;
		std::vector<float> sActivationOutput;
		
	private:
		ConvLayer(
			Activation::Activation *pActivation,
			std::size_t nInputWidth, std::size_t nInputHeight, std::size_t nChannelCount,
			std::size_t nFilterWidth, std::size_t nFilterHeight,
			std::size_t nPaddingWidth, std::size_t nPaddingHeight,
			std::size_t nStrideWidth, std::size_t nStrideHeight);
		ConvLayer(const ConvLayer &sSrc);
		ConvLayer(ConvLayer &&sSrc);
		~ConvLayer();
		
	public:
		ConvLayer &operator=(const ConvLayer &sSrc);
		ConvLayer &operator=(ConvLayer &&sSrc);
		
	public:
		template<class Activation, class ...ActivationConstructorParam> inline static ConvLayer *make(
			std::size_t nInputWidth, std::size_t nInputHeight, std::size_t nChannelCount,
			std::size_t nFilterWidth, std::size_t nFilterHeight,
			std::size_t nPaddingWidth, std::size_t nPaddingHeight,
			std::size_t nStrideWidth, std::size_t nStrideHeight,
			ActivationConstructorParam && ...sParam);
	};
}

#endif