
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

	Span::Span(float *pBegin, float *pEnd) noexcept :
		pBase{pBegin},
		nLength{static_cast<decltype(this->nLength)>(std::distance(pBegin, pEnd))}
	{
		//Empty.
	}

	Span::Span(std::vector<float> &sVector) noexcept :
		pBase{sVector.data()},
		nLength{sVector.size()}
	{
		//Empty.
	}

	Span &Span::operator=(std::vector<float> &sVector) noexcept
	{
		this->pBase = sVector.data();
		this->nLength = sVector.size();

		return *this;
	}

	void Span::__fillScalar(float nScalar) noexcept
	{
		std::fill(this->pBase, this->pBase + this->nLength, nScalar);
	}

	void Span::__copyFrom(const float *pBase, std::size_t nLength) noexcept
	{
		::memcpy_s(this->pBase, this->nLength, pBase, nLength);
	}

	void Span::__accumulateFrom(const float *pBase, std::size_t nLength) noexcept
	{
		std::transform(this->pBase, this->pBase + std::min(this->nLength, nLength), pBase, this->pBase, std::plus<float>{});
	}

	void Span::__accumulateFrom(float nFactor, const float *pBase, std::size_t nLength) noexcept
	{
		std::transform(this->pBase, this->pBase + std::min(this->nLength, nLength), pBase, this->pBase, [=](const auto &nLeft, const auto &nRight)
		{
			return std::fmaf(nRight, nFactor, nLeft);
		});
	}
}