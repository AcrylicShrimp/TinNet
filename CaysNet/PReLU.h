
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_PRE_LU_H

#define _CLASS_CAYSNET_ACTIVATION_PRE_LU_H

#include "Activation.h"

#include <cstddef>

namespace CaysNet::Activation
{
	class PReLU final : public Activation
	{
	private:
		float nFactor;
		
	public:
		PReLU(float nNewFactor);
		PReLU(const PReLU &sSrc);
		~PReLU() = default;
		
	public:
		PReLU &operator=(const PReLU &sSrc);
		PReLU &operator=(float nNewFactor);
		
	public:
		virtual void activate(const Layer *pLayer, float *pOutput) const override;
		virtual void derivative(std::size_t nLength, const float *pInput, const float *pOutput, float *pResult) const override;
		virtual Activation *duplicate() const override;
	};
}

#endif