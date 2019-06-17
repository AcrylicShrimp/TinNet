
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_CONSTANT_H

#define _CLASS_TINNET_INITIALIZER_CONSTANT_H

#include "../TinNetDLL.h"

#include "../Core/Span.h"

#include "Initializer.h"

namespace TinNet::Initializer
{
	class TINNET_DLL Constant : public Initializer
	{
	protected:
		float nConstant;
		
	public:
		Constant(float nConstant = .0f);
		Constant(const Constant &sSrc) = default;
		virtual ~Constant() noexcept = default;
		
	public:
		Constant &operator=(const Constant &sSrc) = default;
		virtual void operator()(Core::Span<float> sSpan) override;
	};
}

#endif