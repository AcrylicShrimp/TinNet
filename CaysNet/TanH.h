
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_TAN_H_H

#define _CLASS_CAYSNET_ACTIVATION_TAN_H_H

#include "Activation.h"

#include <cmath>
#include <cstddef>

namespace CaysNet::Activation
{
	class TanH final : public Activation
	{
	public:
		TanH() = default;
		TanH(const TanH &sSrc) = default;
		TanH(TanH &&sSrc) = default;
		~TanH() = default;
		
	public:
		TanH &operator=(const TanH &sSrc) = default;
		TanH &operator=(TanH &&sSrc) = default;
		
	public:
		virtual void activate(const Layer *pLayer, float *pOutput) const override;
		virtual void derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const override;
		virtual Activation *duplicate() const override;
	};
}

#endif