
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_ACCESSOR_H

#define _CLASS_TINNET_ACCESSOR_H

#include "TinNetDLL.h"

#include "Shape.h"

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace TinNet
{
	class TINNET_DLL Accessor final
	{
	private:
		Shape sShape;
		std::vector<std::size_t> sFactor;

	public:
		Accessor(const Shape &sShape);
		Accessor(const Accessor &sSrc) = default;
		Accessor(Accessor &&sSrc) = default;
		~Accessor() = default;

	public:
		Accessor &operator=(const Shape &sShape);
		Accessor &operator=(const Accessor &sSrc) = default;
		Accessor &operator=(Accessor &&sSrc) = default;
		template<class ...P> inline std::size_t operator()(P &&...sParam) const;

	private:
		template<std::size_t I, class T, class ...P> inline std::size_t operator()(T &&sIndex, P &&...sParam) const;
		template<std::size_t I, class T> inline std::size_t operator()(T &&sIndex) const;

	public:
		inline std::size_t index(std::size_t nAxis, std::size_t nIndex) const;
		template<std::size_t I> inline std::size_t index(std::size_t nIndex) const;
	};

	template<class ...P> inline std::size_t Accessor::operator()(P &&...sParam) const
	{
		return this->operator()<sizeof...(P) - 1>(std::forward<P>(sParam)...);
	}

	template<std::size_t I, class T, class ...P> inline std::size_t Accessor::operator()(T &&sIndex, P &&...sParam) const
	{
		return this->operator()<I>(std::forward<T>(sIndex)) + this->operator()<I - 1>(std::forward<P>(sParam)...);
	}

	template<std::size_t I, class T> inline std::size_t Accessor::operator()(T &&sIndex) const
	{
		return this->index<I>(std::forward<T>(sIndex));
	}

	inline std::size_t Accessor::index(std::size_t nAxis, std::size_t nIndex) const
	{
		std::size_t vIndex[2]
		{
			0,
			this->sFactor.size() - nAxis - 1
		};

		std::size_t vClip[2]
		{
			0,
			nIndex
		};

		vIndex[1] = vIndex[vIndex[1] < this->sFactor.size()];
		return this->sFactor[vIndex[1]] * vClip[vClip[1] < this->sShape[vIndex[1]]];
	}

	template<std::size_t I> inline std::size_t Accessor::index(std::size_t nIndex) const
	{
		std::size_t vIndex[2]
		{
			0,
			this->sFactor.size() - I - 1
		};

		std::size_t vClip[2]
		{
			0,
			nIndex
		};

		vIndex[1] = vIndex[vIndex[1] < this->sFactor.size()];
		return this->sFactor[vIndex[1]] * vClip[vClip[1] < this->sShape[vIndex[1]]];
	}
}

#endif