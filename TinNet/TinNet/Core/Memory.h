
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
	class TINNET_DLL Memory final
	{
	private:
		std::size_t nSize;
		std::size_t nCapacity;
		std::unique_ptr<float[]> sPointer;
		
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
		inline Span span() const noexcept;
		void resize(std::size_t nSize);
		void reserve(std::size_t nCapacity);

	public:
		inline friend void swap(Memory &sLeft, Memory &sRight) noexcept;
	};

	inline std::size_t Memory::size() const noexcept
	{
		return this->nSize;
	}

	inline std::size_t Memory::capacity() const noexcept
	{
		return this->nCapacity;
	}

	inline Span Memory::span() const noexcept
	{
		return Span{this->sPointer.get(), this->nSize};
	}

	inline void swap(Memory &sLeft, Memory &sRight) noexcept
	{
		using std::swap;

		swap(sLeft.nSize, sRight.nSize);
		swap(sLeft.nCapacity, sRight.nCapacity);
		swap(sLeft.sPointer, sRight.sPointer);
	}
}

#endif