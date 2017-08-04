
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_RE_LU_H

#define _CLASS_CAYSNET_ACTIVATION_RE_LU_H

#include "Activation.h"

#include <cstddef>

namespace CaysNet::Activation
{
	class ReLU final : public Activation
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
		virtual void activate(const Layer *pLayer, float *pOutput) const override;
		virtual float derivative(float nZ) const override;
	};
}

#endif