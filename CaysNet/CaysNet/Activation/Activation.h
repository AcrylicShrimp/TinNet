
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _INTERFACE_CAYSNET_ACTIVATION_ACTIVATION_H

#define _INTERFACE_CAYSNET_ACTIVATION_ACTIVATION_H

#include "../CaysNetDLL.h"

#include "../IO/Serializable.h"

#include <cstddef>
#include <utility>

namespace CaysNet::Activation
{
	class CAYSNET_DLL Activation : public IO::Serializable
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
		virtual const wchar_t *name() const = 0;
		virtual Activation *duplicate() const = 0;
		virtual void activate(std::size_t nFanOut, float *pOutput) const = 0;
		virtual void derivative(
			std::size_t nLength,
			const float *pActivationInput,
			const float *pActivationOutput,
			const float *pDerivativeInput,
			float *pResult) const = 0;
		virtual void serialize(std::ofstream &sOutput) const override;
		virtual void deserialize(std::ifstream &sInput) override;
	};
}

#endif