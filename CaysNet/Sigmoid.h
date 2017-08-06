
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_SIGMOID_H

#define _CLASS_CAYSNET_ACTIVATION_SIGMOID_H

#include "Activation.h"

#include <cmath>
#include <cstddef>

namespace CaysNet::Activation
{
	class Sigmoid final : public Activation
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
		virtual void activate(const Layer *pLayer, float *pOutput) const override;
		virtual float derivative(float nZ, float nY) const override;
		virtual Activation *duplicate() const override;
	};
}

#endif