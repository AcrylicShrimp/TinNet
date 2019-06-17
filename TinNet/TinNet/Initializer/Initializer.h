
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_INITIALIZER_H

#define _CLASS_TINNET_INITIALIZER_INITIALIZER_H

#include "../TinNetDLL.h"

#include "../Core/Span.h"

namespace TinNet::Initializer
{
	class TINNET_DLL Initializer
	{
	public:
		Initializer() = default;
		Initializer(const Initializer &sSrc) = default;
		virtual ~Initializer() noexcept = default;
		
	public:
		Initializer &operator=(const Initializer &sSrc) = default;
		virtual void operator()(Core::Span<float> sSpan) = 0;
	};
}

#endif