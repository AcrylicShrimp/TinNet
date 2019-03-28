
/*
	2019.01.15
	Created by AcrylicShrimp.
*/

#include "Memory.h"

namespace TinNet::Core
{
	Memory::Memory() :
		nSize{0},
		nCapacity{0},
		sPointer{}
	{
		//Empty.
	}

	Memory::Memory(std::size_t nSize) :
		nSize{nSize},
		nCapacity{nSize},
		sPointer{std::make_unique<float[]>(nSize)}
	{
		//Empty.
	}

	Memory::Memory(const Memory &sSrc) :
		nSize{sSrc.nSize},
		nCapacity{sSrc.nCapacity},
		sPointer{std::make_unique<float[]>(sSrc.nCapacity)}
	{
		std::memcpy(this->sPointer.get(), sSrc.sPointer.get(), sizeof(float) * sSrc.nSize);
	}

	Memory::Memory(Memory &&sSrc) noexcept :
		nSize{sSrc.nSize},
		nCapacity{sSrc.nCapacity},
		sPointer{std::move(sSrc.sPointer)}
	{
		//Empty.
	}

	Memory &Memory::operator=(Memory sSrc) noexcept
	{
		swap(*this, sSrc);

		return *this;
	}

	Memory &Memory::operator=(Memory &&sSrc) noexcept
	{
		swap(*this, sSrc);

		return *this;
	}

	void Memory::resize(std::size_t nSize)
	{
		if (this->nCapacity >= (this->nSize = nSize))
			return;

		this->sPointer = std::make_unique<float[]>(this->nCapacity = nSize);
	}

	void Memory::reserve(std::size_t nCapacity)
	{
		if (this->nCapacity >= nCapacity)
			return;

		this->sPointer = std::make_unique<float[]>(this->nCapacity = nCapacity);
	}
}