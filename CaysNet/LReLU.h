
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_LRE_LU_H

#define _CLASS_CAYSNET_ACTIVATION_LRE_LU_H

#include "Activation.h"

#include <cstddef>

namespace CaysNet::Activation
{
	class LReLU final : public Activation
	{
	public:
		LReLU() = default;
		LReLU(const LReLU &sSrc) = default;
		LReLU(LReLU &&sSrc) = default;
		~LReLU() = default;
		
	public:
		LReLU &operator=(const LReLU &sSrc) = default;
		LReLU &operator=(LReLU &&sSrc) = default;
		
	public:
		virtual void activate(const Layer *pLayer, float *pOutput) const override;
		virtual void derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const override;
		virtual Activation *duplicate() const override;
	};
}

#endif