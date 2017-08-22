
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_RE_LU_H

#define _CLASS_CAYSNET_ACTIVATION_RE_LU_H

#include "../CaysNetDLL.h"

#include "Activation.h"

#include <cstddef>

namespace CaysNet::Activation
{
	class CAYSNET_DLL ReLU final : public Activation
	{
	public:
		ReLU() = default;
		ReLU(const ReLU &sSrc) = default;
		ReLU(ReLU &&sSrc) = default;
		~ReLU() = default;
		
	public:
		ReLU &operator=(const ReLU &sSrc) = default;
		ReLU &operator=(ReLU &&sSrc) = default;
		
	public:
		virtual const wchar_t *name() const override;
		virtual Activation *duplicate() const override;
		virtual void activate(const Layer *pLayer, float *pOutput) const override;
		virtual void derivative(
			std::size_t nLength,
			const float *pActivationInput,
			const float *pActivationOutput,
			const float *pDerivativeInput,
			float *pResult) const override;
	};
}

#endif