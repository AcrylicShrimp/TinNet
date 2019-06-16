
/*
	2019.01.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_MEMORY_H

#define _CLASS_TINNET_CORE_MEMORY_H

#include "../TinNetDLL.h"

#include "Span.h"

#include <cstring>
#include <memory>
#include <utility>

namespace TinNet::Core
{
	template<class T> class Memory final
	{
	private:
		std::size_t nSize;
		std::size_t nCapacity;
		std::unique_ptr<T[]> sPointer;

	public:
		Memory();
		Memory(std::size_t nSize);
		Memory(const Memory &sSrc);
		Memory(Memory &&sSrc) noexcept;
		~Memory() noexcept = default;

	public:
		Memory &operator=(Memory sSrc) noexcept;
		Memory &operator=(Memory &&sSrc) noexcept;

	public:
		inline std::size_t size() const noexcept;
		inline std::size_t capacity() const noexcept;
		inline Span<T> span() const noexcept;
		void resize(std::size_t nSize);
		void reserve(std::size_t nCapacity);

	public:
		template<class T> inline friend void swap(Memory<T> &sLeft, Memory<T> &sRight) noexcept;
	};

	template<class T> inline std::size_t Memory<T>::size() const noexcept
	{
		return this->nSize;
	}

	template<class T> inline std::size_t Memory<T>::capacity() const noexcept
	{
		return this->nCapacity;
	}

	template<class T> inline Span<T> Memory<T>::span() const noexcept
	{
		return Span{this->sPointer.get(), this->nSize};
	}

	template<class T> inline void swap(Memory<T> &sLeft, Memory<T> &sRight) noexcept
	{
		using std::swap;

		swap(sLeft.nSize, sRight.nSize);
		swap(sLeft.nCapacity, sRight.nCapacity);
		swap(sLeft.sPointer, sRight.sPointer);
	}
}

#include "Memory.hpp"

#endif