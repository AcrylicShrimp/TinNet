
/*
	2018.10.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_SPAN_H

#define _CLASS_TINNET_CORE_SPAN_H

#include "../TinNetDLL.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iterator>
#include <utility>

namespace TinNet::Core
{
	class TINNET_DLL Span final
	{
	private:
		float *pBase;
		std::size_t nLength;

	public:
		Span() noexcept;
		Span(float *pBase, std::size_t nLength) noexcept;
		template<class I> inline Span(I iBegin, I iEnd) noexcept;
		Span(const Span &sSrc) noexcept = default;
		~Span() noexcept = default;

	public:
		Span &operator=(const Span &sSrc) noexcept = default;
		inline float &operator[](std::size_t nIndex);
		inline const float &operator[](std::size_t nIndex) const;

	public:
		inline float *begin() noexcept;
		inline const float *begin() const noexcept;
		inline const float *cbegin() const noexcept;
		inline float *end() noexcept;
		inline const float *end() const noexcept;
		inline const float *cend() const noexcept;
		inline std::size_t length() const noexcept;
		inline Span subSpan(std::size_t nOffset) const noexcept;
		inline Span subSpan(std::size_t nOffset, std::size_t nLength) const noexcept;
		inline void fillZero();
		inline void fillOne();
		inline void fillScalar(float nScalar);
		inline void copyFrom(const Span &sSpan);
		template<class I> inline void copyFrom(I iBegin, I iEnd);
		inline void accumulateFrom(const Span &sSpan);
		template<class I> inline void accumulateFrom(I iBegin, I iEnd);
		inline void accumulateFrom(float nFactor, const Span &sSpan);
		template<class I> inline void accumulateFrom(float nFactor, I iBegin, I iEnd);

	public:
		inline friend void swap(Span &sLeft, Span &sRight) noexcept;
	};

	template<class I> inline Span::Span(I iBegin, I iEnd) noexcept :
		pBase{&*iBegin},
		nLength{static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd))}
	{
		//Empty.
	}

	inline float &Span::operator[](std::size_t nIndex)
	{
		return this->pBase[nIndex];
	}

	inline const float &Span::operator[](std::size_t nIndex) const
	{
		return this->pBase[nIndex];
	}

	inline float *Span::begin() noexcept
	{
		return this->pBase;
	}

	inline const float *Span::begin() const noexcept
	{
		return this->pBase;
	}

	inline const float *Span::cbegin() const noexcept
	{
		return this->pBase;
	}

	inline float *Span::end() noexcept
	{
		return this->pBase + this->nLength;
	}

	inline const float *Span::end() const noexcept
	{
		return this->pBase + this->nLength;
	}

	inline const float *Span::cend() const noexcept
	{
		return this->pBase + this->nLength;
	}

	inline std::size_t Span::length() const noexcept
	{
		return this->nLength;
	}

	inline Span Span::subSpan(std::size_t nOffset) const noexcept
	{
		return Span{this->pBase + nOffset, this->pBase + this->nLength};
	}

	inline Span Span::subSpan(std::size_t nOffset, std::size_t nLength) const noexcept
	{
		return Span{this->pBase + nOffset, this->pBase + std::min(this->nLength, nLength)};
	}

	inline void Span::fillZero()
	{
		std::fill(this->pBase, this->pBase + this->nLength, .0f);
	}

	inline void Span::fillOne()
	{
		std::fill(this->pBase, this->pBase + this->nLength, 1.f);
	}

	inline void Span::fillScalar(float nScalar)
	{
		std::fill(this->pBase, this->pBase + this->nLength, nScalar);
	}

	inline void Span::copyFrom(const Span &sSpan)
	{
		std::copy(sSpan.pBase, sSpan.pBase + std::min(sSpan.nLength, this->nLength), this->pBase);
	}

	template<class I> inline void Span::copyFrom(I iBegin, I iEnd)
	{
		std::copy(iBegin, iBegin + std::min(static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd)), this->nLength), this->pBase);
	}

	inline void Span::accumulateFrom(const Span &sSpan)
	{
		std::transform(sSpan.pBase, sSpan.pBase + std::min(sSpan.nLength, this->nLength), this->pBase, this->pBase, std::plus<float>{});
	}

	template<class I> inline void Span::accumulateFrom(I iBegin, I iEnd)
	{
		std::transform(iBegin, iBegin + std::min(static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd)), this->nLength), this->pBase, this->pBase, std::plus<float>{});
	}

	inline void Span::accumulateFrom(float nFactor, const Span &sSpan)
	{
		std::transform(sSpan.pBase, sSpan.pBase + std::min(sSpan.nLength, this->nLength), this->pBase, this->pBase, [=](auto nLeft, auto nRight) { return std::fmaf(nLeft, nFactor, nRight); });
	}

	template<class I> inline void Span::accumulateFrom(float nFactor, I iBegin, I iEnd)
	{
		std::transform(iBegin, iBegin + std::min(static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd)), this->nLength), this->pBase, this->pBase, [=](auto nLeft, auto nRight) { return std::fmaf(nLeft, nFactor, nRight); });
	}

	inline void swap(Span &sLeft, Span &sRight) noexcept
	{
		using std::swap;

		swap(sLeft.pBase, sRight.pBase);
		swap(sLeft.nLength, sRight.nLength);
	}
}

#endif