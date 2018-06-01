
/*
	2018.05.29
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_ITERATOR_H

#define _CLASS_TINNET_ITERATOR_H

#include "Accessor.h"
#include "Shape.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace TinNet
{
	template<class ...P> class Iterator
	{
	private:
		Shape sShape;
		std::size_t nAxis;
		std::size_t nMaxAxis;
		std::vector<std::size_t> sAxis;
		std::vector<std::size_t> sIndex;
		std::vector<Accessor> sAccessor;
		bool bContinue;

	public:
		Iterator();
		Iterator(const Iterator &sSrc) = default;
		Iterator(Iterator &&sSrc) = default;
		~Iterator() = default;

	public:
		Iterator &operator=(const Iterator &sSrc) = default;
		Iterator &operator=(Iterator &&sSrc) = default;
		inline operator bool() const;
		Iterator &operator++();

	public:
		void init(const Shape &sShape, const P &...sAccessor);
		void prepare();
		void prepare(std::size_t nBeginAxis);
		void prepare(std::size_t nBeginAxis, std::size_t nEndAxis);
		template<std::size_t I> inline std::size_t index() const;
		template<std::size_t I> inline const Accessor &accessor() const;

	private:
		void decrement(std::size_t nAxis);
		void increment(std::size_t nAxis);
		template<std::size_t I = sizeof...(P) - 1> void increment(std::size_t nAxis);
		template<> void increment<0>(std::size_t nAxis);
	};

	template<class ...P> inline Iterator<P...>::operator bool() const
	{
		return this->bContinue;
	}

	template<class ...P> template<std::size_t I> inline std::size_t Iterator<P...>::index() const
	{
		return this->sIndex[I];
	}

	template<class ...P> template<std::size_t I> inline const Accessor &Iterator<P...>::accessor() const
	{
		return this->sAccessor[I];
	}
}

#include "Iterator.hpp"

#endif