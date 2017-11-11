
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_SIGMOID_H

#define _CLASS_CAYSNET_ACTIVATION_SIGMOID_H

#include "../CaysNetDLL.h"

#include "Activation.h"

#include <cmath>
#include <cstddef>

namespace CaysNet::Activation
{
	class CAYSNET_DLL Sigmoid final : public Activation
	{
	public:
		Sigmoid() = default;
		Sigmoid(const Sigmoid &sSrc) = default;
		Sigmoid(Sigmoid &&sSrc) = default;
		~Sigmoid() = default;
		
	public:
		Sigmoid &operator=(const Sigmoid &sSrc) = default;
		Sigmoid &operator=(Sigmoid &&sSrc) = default;
		
	public:
		virtual const wchar_t *name() const override;
		virtual Activation *duplicate() const override;
		virtual void activate(std::size_t nFanOut, float *pOutput) const override;
		virtual void derivative(
			std::size_t nLength,
			const float *pActivationInput,
			const float *pActivationOutput,
			const float *pDerivativeInput,
			float *pResult) const override;
	};
}

#endif