
/*
	2018.10.13
	Created by AcrylicShrimp.
*/

#include "Span.h"

namespace TinNet::Core
{
	Span::Span() noexcept :
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
}