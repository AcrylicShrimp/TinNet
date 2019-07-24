
/*
	2018.10.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_SPAN_H

#define _CLASS_TINNET_CORE_SPAN_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iterator>
#include <utility>

namespace TinNet::Core
{
	template<class T> class Span final
	{
	private:
		T *pBase;
		std::size_t nLength;

	public:
		Span() noexcept;
		Span(T *pBase, std::size_t nLength) noexcept;
		template<class I> inline Span(I iBegin, I iEnd) noexcept;
		Span(const Span &sSrc) noexcept = default;
		~Span() noexcept = default;

	public:
		Span &operator=(const Span &sSrc) noexcept = default;
		inline T &operator[](std::size_t nIndex);
		inline const T &operator[](std::size_t nIndex) const;

	public:
		inline T *begin() noexcept;
		inline const T *begin() const noexcept;
		inline const T *cbegin() const noexcept;
		inline T *end() noexcept;
		inline const T *end() const noexcept;
		inline const T *cend() const noexcept;
		inline std::size_t length() const noexcept;
		inline T *min();
		inline const T *min() const;
		inline T *max();
		inline const T *max() const;
		inline Span subSpan(std::size_t nOffset) const noexcept;
		inline Span subSpan(std::size_t nOffset, std::size_t nLength) const noexcept;
		inline void fillZero();
		inline void fillOne();
		inline void fillScalar(T tScalar);
		inline void copyFrom(const Span &sSpan);
		template<class I> inline void copyFrom(I iBegin, I iEnd);
		inline void accumulateFrom(const Span &sSpan);
		template<class I> inline void accumulateFrom(I iBegin, I iEnd);
		inline void accumulateFrom(T tFactor, const Span &sSpan);
		template<class I> inline void accumulateFrom(T tFactor, I iBegin, I iEnd);

	public:
		template<class T> inline friend void swap(Span &sLeft, Span &sRight) noexcept;
	};

	template<class T> template<class I> inline Span<T>::Span(I iBegin, I iEnd) noexcept :
		pBase{&*iBegin},
		nLength{static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd))}
	{
		//Empty.
	}

	template<class T> inline T &Span<T>::operator[](std::size_t nIndex)
	{
		return this->pBase[nIndex];
	}

	template<class T> inline const T &Span<T>::operator[](std::size_t nIndex) const
	{
		return this->pBase[nIndex];
	}

	template<class T> inline T *Span<T>::begin() noexcept
	{
		return this->pBase;
	}

	template<class T> inline const T *Span<T>::begin() const noexcept
	{
		return this->pBase;
	}

	template<class T> inline const T *Span<T>::cbegin() const noexcept
	{
		return this->pBase;
	}

	template<class T> inline T *Span<T>::end() noexcept
	{
		return this->pBase + this->nLength;
	}

	template<class T> inline const T *Span<T>::end() const noexcept
	{
		return this->pBase + this->nLength;
	}

	template<class T> inline const T *Span<T>::cend() const noexcept
	{
		return this->pBase + this->nLength;
	}

	template<class T> inline std::size_t Span<T>::length() const noexcept
	{
		return this->nLength;
	}

	template<class T> inline T *Span<T>::min()
	{
		return std::min_element(this->begin(), this->end());
	}

	template<class T> inline const T *Span<T>::min() const
	{
		return std::min_element(this->cbegin(), this->cend());
	}

	template<class T> inline T *Span<T>::max()
	{
		return std::max_element(this->begin(), this->end());
	}

	template<class T> inline const T *Span<T>::max() const
	{
		return std::max_element(this->cbegin(), this->cend());
	}

	template<class T> inline Span<T> Span<T>::subSpan(std::size_t nOffset) const noexcept
	{
		return Span{this->pBase + nOffset, this->pBase + this->nLength};
	}

	template<class T> inline Span<T> Span<T>::subSpan(std::size_t nOffset, std::size_t nLength) const noexcept
	{
		return Span{this->pBase + nOffset, this->pBase + std::min(this->nLength, nLength)};
	}

	template<class T> inline void Span<T>::fillZero()
	{
		std::fill(this->pBase, this->pBase + this->nLength, static_cast<T>(0));
	}

	template<class T> inline void Span<T>::fillOne()
	{
		std::fill(this->pBase, this->pBase + this->nLength, static_cast<T>(1));
	}

	template<class T> inline void Span<T>::fillScalar(T tScalar)
	{
		std::fill(this->pBase, this->pBase + this->nLength, tScalar);
	}

	template<class T> inline void Span<T>::copyFrom(const Span &sSpan)
	{
		std::copy(sSpan.pBase, sSpan.pBase + std::min(sSpan.nLength, this->nLength), this->pBase);
	}

	template<class T> template<class I> inline void Span<T>::copyFrom(I iBegin, I iEnd)
	{
		std::copy(iBegin, iBegin + std::min(static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd)), this->nLength), this->pBase);
	}

	template<class T> inline void Span<T>::accumulateFrom(const Span &sSpan)
	{
		std::transform(sSpan.pBase, sSpan.pBase + std::min(sSpan.nLength, this->nLength), this->pBase, this->pBase, std::plus<T>{});
	}

	template<class T> template<class I> inline void Span<T>::accumulateFrom(I iBegin, I iEnd)
	{
		std::transform(iBegin, iBegin + std::min(static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd)), this->nLength), this->pBase, this->pBase, std::plus<T>{});
	}

	template<class T> inline void Span<T>::accumulateFrom(T tFactor, const Span &sSpan)
	{
		std::transform(sSpan.pBase, sSpan.pBase + std::min(sSpan.nLength, this->nLength), this->pBase, this->pBase, [=](auto nLeft, auto nRight) { return std::fma(nLeft, tFactor, nRight); });
	}

	template<class T> template<class I> inline void Span<T>::accumulateFrom(T tFactor, I iBegin, I iEnd)
	{
		std::transform(iBegin, iBegin + std::min(static_cast<decltype(this->nLength)>(std::distance(iBegin, iEnd)), this->nLength), this->pBase, this->pBase, [=](auto nLeft, auto nRight) { return std::fma(nLeft, tFactor, nRight); });
	}

	template<class T> inline void swap(Span<T> &sLeft, Span<T> &sRight) noexcept
	{
		using std::swap;

		swap(sLeft.pBase, sRight.pBase);
		swap(sLeft.nLength, sRight.nLength);
	}
}

#include "Span.hpp"

#endif