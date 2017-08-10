
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_SOFTMAX_H

#define _CLASS_CAYSNET_ACTIVATION_SOFTMAX_H

#include "Activation.h"

#include <cmath>
#include <cstddef>

namespace CaysNet::Activation
{
	class Softmax final : public Activation
	{
	public:
		Softmax() = default;
		Softmax(const Softmax &sSrc) = default;
		Softmax(Softmax &&sSrc) = default;
		~Softmax() = default;
		
	public:
		Softmax &operator=(const Softmax &sSrc) = default;
		Softmax &operator=(Softmax &&sSrc) = default;
		
	public:
		virtual void activate(const Layer *pLayer, float *pOutput) const override;
		virtual void derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const override;
		virtual Activation *duplicate() const override;
	};
}

#endif