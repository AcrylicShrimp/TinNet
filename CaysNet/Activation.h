
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_ACTIVATION_H

#define _CLASS_CAYSNET_ACTIVATION_ACTIVATION_H

#include "Layer.h"

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
		virtual void activate(const Layer *pLayer, float *pOutput) const = 0;
		virtual float derivative(float nZ, float nY) const = 0;
		virtual Activation *duplicate() const = 0;
	};
}

#endif