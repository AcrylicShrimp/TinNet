
/*
	2019.06.15
	Created by AcrylicShrimp.
*/

namespace TinNet::Core
{
	template<class T> Memory<T>::Memory() :
		nSize{0},
		nCapacity{0},
		sPointer{}
	{
		//Empty.
	}

	template<class T> Memory<T>::Memory(std::size_t nSize) :
		nSize{nSize},
		nCapacity{nSize},
		sPointer{std::make_unique<T[]>(nSize)}
	{
		//Empty.
	}

	template<class T> Memory<T>::Memory(const Memory &sSrc) :
		nSize{sSrc.nSize},
		nCapacity{sSrc.nCapacity},
		sPointer{std::make_unique<T[]>(sSrc.nCapacity)}
	{
		std::memcpy(this->sPointer.get(), sSrc.sPointer.get(), sizeof(T) *sSrc.nSize);
	}

	template<class T> Memory<T>::Memory(Memory &&sSrc) noexcept :
		nSize{sSrc.nSize},
		nCapacity{sSrc.nCapacity},
		sPointer{std::move(sSrc.sPointer)}
	{
		//Empty.
	}

	template<class T> Memory<T> &Memory<T>::operator=(Memory sSrc) noexcept
	{
		swap(*this, sSrc);

		return *this;
	}

	template<class T> Memory<T> &Memory<T>::operator=(Memory &&sSrc) noexcept
	{
		swap(*this, sSrc);

		return *this;
	}

	template<class T> void Memory<T>::resize(std::size_t nSize)
	{
		if (this->nCapacity >= (this->nSize = nSize))
			return;

		this->sPointer = std::make_unique<T[]>(this->nCapacity = nSize);
	}

	template<class T> void Memory<T>::reserve(std::size_t nCapacity)
	{
		if (this->nCapacity >= nCapacity)
			return;

		this->sPointer = std::make_unique<T[]>(this->nCapacity = nCapacity);
	}
}