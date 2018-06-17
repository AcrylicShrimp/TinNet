
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_SHAPE_H

#define _CLASS_TINNET_SHAPE_H

#include "TinNetDLL.h"

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>

namespace TinNet
{
	class TINNET_DLL Shape final
	{
	private:
		std::size_t nElement;
		std::vector<std::size_t> sShape;

	public:
		Shape();
		Shape(std::initializer_list<std::size_t> sShape);
		Shape(const std::vector<std::size_t> &sShape);
		Shape(std::vector<std::size_t> &&sShape);
		Shape(const Shape &sSrc) = default;
		Shape(Shape &&sSrc) = default;
		~Shape() = default;

	public:
		Shape &operator=(std::initializer_list<std::size_t> sShape);
		Shape &operator=(const std::vector<std::size_t> &sShape);
		Shape &operator=(const Shape &sSrc) = default;
		Shape &operator=(Shape &&sSrc) = default;
		bool operator==(std::initializer_list<std::size_t> sShape) const;
		bool operator==(const std::vector<std::size_t> &sShape) const;
		bool operator==(const Shape &sShape) const;
		bool operator!=(std::initializer_list<std::size_t> sShape) const;
		bool operator!=(const std::vector<std::size_t> &sShape) const;
		bool operator!=(const Shape &sShape) const;
		inline std::size_t operator[](std::size_t nAxis) const;

	public:
		inline std::size_t rank() const;
		inline std::size_t size(std::size_t nAxis) const;
		inline std::size_t element() const;
		Shape shrink() const;
		Shape expand() const;
		Shape expand(std::size_t nRank) const;
		Shape squeeze() const;
		void set(std::size_t nAxis, std::size_t nSize);
		static Shape broadcast(const Shape &sLeft, const Shape &sRight);
	};

	inline std::size_t Shape::operator[](std::size_t nAxis) const
	{
		return this->sShape[nAxis];
	}

	inline std::size_t Shape::rank() const
	{
		return this->sShape.size();
	}

	inline std::size_t Shape::size(std::size_t nAxis) const
	{
		return nAxis < this->sShape.size() ? this->sShape[nAxis] : 1;
	}

	inline std::size_t Shape::element() const
	{
		return this->nElement;
	}
}

#endif