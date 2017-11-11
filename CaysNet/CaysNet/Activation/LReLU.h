
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_LRE_LU_H

#define _CLASS_CAYSNET_ACTIVATION_LRE_LU_H

#include "../CaysNetDLL.h"

#include "Activation.h"

#include <cstddef>

namespace CaysNet::Activation
{
	class CAYSNET_DLL LReLU final : public Activation
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
		virtual const wchar_t *name() const override;
		virtual Activation *duplicate() const override;
		virtual void activate(std::size_t nFanOut, float *pOutput) const override;
		virtual void derivative(std::size_t nLength, const float *pLayerInput, const float *pActivationInput, const float *pActivationOutput, float *pResult) const override;
	};
}

#endif