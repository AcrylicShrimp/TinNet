
/*
	2019.03.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_INITIALIZERWRAPPER_H

#define _CLASS_TINNET_CORE_INITIALIZERWRAPPER_H

#include "../TinNetDLL.h"

#include "../Core/Span.h"

#include "../Initializer/Initializer.h"

namespace TinNet::Core
{
	class TINNET_DLL InitializerWrapper final
	{
	public:
		Initializer::Initializer *const pInitializer;

	public:
		InitializerWrapper(Initializer::Initializer *pInitializer);
		InitializerWrapper(const InitializerWrapper &sSrc) = default;
		~InitializerWrapper() noexcept = default;

	public:
		InitializerWrapper &operator=(const InitializerWrapper &sSrc) = delete;
		inline void operator()(Core::Span<float> sSpan);
		inline operator Initializer::Initializer *() noexcept;
		inline operator const Initializer::Initializer *() const noexcept;
	};

	inline void InitializerWrapper::operator()(Core::Span<float> sSpan)
	{
		this->pInitializer->operator()(sSpan);
	}

	inline InitializerWrapper::operator Initializer::Initializer *() noexcept
	{
		return this->pInitializer;
	}

	inline InitializerWrapper::operator const Initializer::Initializer *() const noexcept
	{
		return this->pInitializer;
	}
}

#endif