
/*
	2018.10.13
	Created by AcrylicShrimp.
*/

#include "Span.h"

namespace TinNet::Core
{
	constexpr Span::Span() noexcept :
		pBase{nullptr},
		nLength{0}
	{
		//Empty.
	}

	Span::Span(float *pBase, std::size_t nLength) noexcept :
		pBase{pBase},
		nLength{nLength}
	{
		//Empty.
	}

	template<class I> Span::Span(I iBegin, I iEnd) noexcept :
		pBase{&*iBegin},
		nLength{static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd))}
	{
		//Empty.
	}
}