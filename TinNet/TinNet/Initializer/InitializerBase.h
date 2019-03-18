
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_INITIALIZERBASE_H

#define _CLASS_TINNET_INITIALIZER_INITIALIZERBASE_H

#include "../TinNetDLL.h"

#include "../Core/Span.h"

namespace TinNet::Initializer
{
	class TINNET_DLL InitializerBase
	{
	public:
		InitializerBase() = default;
		InitializerBase(const InitializerBase &sSrc) = default;
		virtual ~InitializerBase() noexcept = default;
		
	public:
		InitializerBase &operator=(const InitializerBase &sSrc) = default;
		
	public:
		virtual void operator()(Core::Span sSpan) = 0;
	};
}

#endif