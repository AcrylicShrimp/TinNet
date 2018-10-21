
/*
	2018.10.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_SPAN_H

#define _CLASS_TINNET_CORE_SPAN_H

#include "../TinNetDLL.h"

#include <algorithm>	//std::min, std::fill, std::transform
#include <cmath>		//std::fmaf
#include <cstddef>		//std::size_t
#include <cstring>		//::memcpy_s
#include <functional>	//std::plus
#include <iterator>		//std::distance
#include <vector>		//std::vector

namespace TinNet::Core
{
	class TINNET_DLL Span final
	{
	private:
		float *pBase;
		std::size_t nLength;

	public:
		Span() noexcept;
		Span(const Span &sSrc) noexcept = default;
		Span(float *pBase, std::size_t nLength) noexcept;
		Span(float *pBegin, float *pEnd) noexcept;
		Span(std::vector<float> &sVector) noexcept;
		template<std::size_t Length> inline Span(float(&vArray)[Length]) noexcept;
		~Span() noexcept = default;

	public:
		Span &operator=(const Span &sSrc) noexcept = default;
		Span &operator=(std::vector<float> &sVector) noexcept;
		template<std::size_t Length> inline Span &operator=(float(&vArray)[Length]) noexcept;
		inline float &operator[](std::size_t nIndex) noexcept;
		inline const float &operator[](std::size_t nIndex) const noexcept;

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
		inline void fillZero() noexcept;
		inline void fillOne() noexcept;
		inline void fillScalar(float nScalar) noexcept;
		inline void copyFrom(const Span &sSpan) noexcept;
		inline void copyFrom(const float *pBase, std::size_t nLength) noexcept;
		inline void copyFrom(const float *pBegin, const float *pEnd) noexcept;
		inline void copyFrom(const std::vector<float> &sVector) noexcept;
		template<std::size_t Length> inline void copyFrom(const float(&vArray)[Length]) noexcept;
		inline void accumulateFrom(const Span &sSpan) noexcept;
		inline void accumulateFrom(const float *pBase, std::size_t nLength) noexcept;
		inline void accumulateFrom(const float *pBegin, const float *pEnd) noexcept;
		inline void accumulateFrom(const std::vector<float> &sVector) noexcept;
		template<std::size_t Length> inline void accumulateFrom(const float(&vArray)[Length]) noexcept;
		inline void accumulateFrom(float nFactor, const Span &sSpan) noexcept;
		inline void accumulateFrom(float nFactor, const float *pBase, std::size_t nLength) noexcept;
		inline void accumulateFrom(float nFactor, const float *pBegin, const float *pEnd) noexcept;
		inline void accumulateFrom(float nFactor, const std::vector<float> &sVector) noexcept;
		template<std::size_t Length> inline void accumulateFrom(float nFactor, const float(&vArray)[Length]) noexcept;

	private:
		void __fillScalar(float nScalar) noexcept;
		void __copyFrom(const float *pBase, std::size_t nLength) noexcept;
		void __accumulateFrom(const float *pBase, std::size_t nLength) noexcept;
		void __accumulateFrom(float nFactor, const float *pBase, std::size_t nLength) noexcept;
	};

	template<std::size_t Length> inline Span::Span(float(&vArray)[Length]) noexcept :
		Span(vArray, Length)
	{
		//Empty.
	}

	template<std::size_t Length> inline Span &Span::operator=(float(&vArray)[Length]) noexcept
	{
		this->pBase = vArray;
		this->nLength = Length;

		return *this;
	}

	inline float &Span::operator[](std::size_t nIndex) noexcept
	{
		return this->pBase[nIndex];
	}

	inline const float &Span::operator[](std::size_t nIndex) const noexcept
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
		return {this->pBase + nOffset, this->nLength < nOffset ? 0 : this->nLength - nOffset};
	}

	inline Span Span::subSpan(std::size_t nOffset, std::size_t nLength) const noexcept
	{
		return {this->pBase + nOffset, this->nLength < nOffset ? 0 : std::min(this->nLength - nOffset, nLength)};
	}

	inline void Span::fillZero() noexcept
	{
		this->__fillScalar(.0f);
	}

	inline void Span::fillOne() noexcept
	{
		this->__fillScalar(1.f);
	}

	inline void Span::fillScalar(float nScalar) noexcept
	{
		this->__fillScalar(nScalar);
	}

	inline void Span::copyFrom(const Span &sSpan) noexcept
	{
		this->__copyFrom(sSpan.cbegin(), sSpan.length());
	}

	inline void Span::copyFrom(const float *pBase, std::size_t nLength) noexcept
	{
		this->__copyFrom(pBase, nLength);
	}

	inline void Span::copyFrom(const float *pBegin, const float *pEnd) noexcept
	{
		this->__copyFrom(pBegin, std::distance(pBegin, pEnd));
	}

	inline void Span::copyFrom(const std::vector<float> &sVector) noexcept
	{
		this->__copyFrom(sVector.data(), sVector.size());
	}

	template<std::size_t Length> inline void Span::copyFrom(const float(&vArray)[Length]) noexcept
	{
		this->copyFrom(vArray, Length);
	}

	inline void Span::accumulateFrom(const Span &sSpan) noexcept
	{
		this->__accumulateFrom(sSpan.cbegin(), sSpan.length());
	}

	inline void Span::accumulateFrom(const float *pBase, std::size_t nLength) noexcept
	{
		this->__accumulateFrom(pBase, nLength);
	}

	inline void Span::accumulateFrom(const float *pBegin, const float *pEnd) noexcept
	{
		this->__accumulateFrom(pBegin, std::distance(pBegin, pEnd));
	}

	inline void Span::accumulateFrom(const std::vector<float> &sVector) noexcept
	{
		this->__accumulateFrom(sVector.data(), sVector.size());
	}

	template<std::size_t Length> inline void Span::accumulateFrom(const float(&vArray)[Length]) noexcept
	{
		this->accumulateFrom(vArray, Length);
	}

	inline void Span::accumulateFrom(float nFactor, const Span &sSpan) noexcept
	{
		this->__accumulateFrom(nFactor, sSpan.cbegin(), sSpan.length());
	}

	inline void Span::accumulateFrom(float nFactor, const float *pBase, std::size_t nLength) noexcept
	{
		this->__accumulateFrom(nFactor, pBase, nLength);
	}

	inline void Span::accumulateFrom(float nFactor, const float *pBegin, const float *pEnd) noexcept
	{
		this->__accumulateFrom(nFactor, pBegin, std::distance(pBegin, pEnd));
	}

	inline void Span::accumulateFrom(float nFactor, const std::vector<float> &sVector) noexcept
	{
		this->__accumulateFrom(nFactor, sVector.data(), sVector.size());
	}

	template<std::size_t Length> inline void Span::accumulateFrom(float nFactor, const float(&vArray)[Length]) noexcept
	{
		this->accumulateFrom(nFactor, vArray, Length);
	}
}

#endif