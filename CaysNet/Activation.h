
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_ACTIVATION_H

#define _CLASS_CAYSNET_ACTIVATION_ACTIVATION_H

#include "Layer.h"

#include <cstddef>
#include <utility>

namespace CaysNet::Activation
{
	class Activation
	{
	public:
		Activation() = default;
		Activation(const Activation &sSrc) = default;
		Activation(Activation &&sSrc) = default;
		virtual ~Activation() = default;
		
	public:
		Activation &operator=(const Activation &sSrc) = default;
		Activation &operator=(Activation &&sSrc) = default;

	public:
		virtual Activation *duplicate() const = 0;
		virtual void activate(const Layer *pLayer, float *pOutput) const = 0;
		virtual void derivative(
			std::size_t nLength,
			const float *pActivationInput,
			const float *pActivationOutput,
			const float *pDerivativeInput,
			float *pResult) const = 0;
	};
}

#endif