
/*
	2018.10.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_SHAPE_H

#define _CLASS_TINNET_CORE_SHAPE_H

#include "../TinNetDLL.h"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace TinNet::Core
{
	class TINNET_DLL Shape final
	{
	private:
		std::vector<std::size_t> sDimension;

	public:
		Shape();
		Shape(std::initializer_list<std::size_t> sDimension);
		Shape(const Shape &sSrc) = default;
		Shape(Shape &&sSrc) noexcept = default;
		template<class I> Shape(I iBegin, I iEnd);
		~Shape() noexcept = default;

	public:
		Shape &operator=(std::initializer_list<std::size_t> sDimension);
		Shape &operator=(const Shape &sSrc) = default;
		Shape &operator=(Shape &&sSrc) noexcept = default;
		bool operator==(std::initializer_list<std::size_t> sDimension) const;
		bool operator==(const Shape &sShape) const;
		bool operator!=(std::initializer_list<std::size_t> sDimension) const;
		bool operator!=(const Shape &sShape) const;
		inline std::size_t &operator[](std::size_t nAxis);
		inline std::size_t operator[](std::size_t nAxis) const;

	public:
		inline std::size_t rank() const noexcept;
		inline std::size_t size() const noexcept;
		Shape expand() const;
		Shape expand(std::size_t nRank) const;
		Shape shrink() const;
		Shape squeeze() const;
		static Shape broadcast(const Shape &sLeft, const Shape &sRight);
		template<class I> void assign(I iBegin, I iEnd);
		template<class I> bool equals(I iBegin, I iEnd) const;

	public:
		inline friend void swap(Shape &sLeft, Shape &sRight) noexcept;
	};

	inline std::size_t &Shape::operator[](std::size_t nAxis)
	{
		return this->sDimension[nAxis];
	}

	inline std::size_t Shape::operator[](std::size_t nAxis) const
	{
		return this->sDimension[nAxis];
	}

	inline std::size_t Shape::rank() const noexcept
	{
		return this->sDimension.size();
	}

	inline std::size_t Shape::size() const noexcept
	{
		return std::accumulate(this->sDimension.cbegin(), this->sDimension.cend(), static_cast<std::size_t>(1), std::multiplies<std::size_t>{});
	}

	inline void swap(Shape &sLeft, Shape &sRight) noexcept
	{
		using std::swap;

		swap(sLeft.sDimension, sRight.sDimension);
	}
}

#include "Shape.hpp"

#endif