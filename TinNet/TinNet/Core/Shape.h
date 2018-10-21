
/*
	2018.10.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_SHAPE_H

#define _CLASS_TINNET_CORE_SHAPE_H

#include "../TinNetDLL.h"

#include <algorithm>	//std::max
#include <cstddef>		//std::size_t
#include <stdexcept>	//std::invalid_argument
#include <utility>		//std::move
#include <vector>		//std::vector

namespace TinNet::Core
{
	class TINNET_DLL Shape final
	{
	private:
		std::size_t nElement;
		std::vector<std::size_t> sDimension;

	public:
		Shape();
		Shape(const std::vector<std::size_t> &sDimension);
		Shape(std::vector<std::size_t> &&sDimension);
		Shape(const Shape &sSrc) = default;
		Shape(Shape &&sSrc) = default;
		~Shape() noexcept = default;

	public:
		Shape &operator=(const std::vector<std::size_t> &sDimension);
		Shape &operator=(std::vector<std::size_t> &&sDimension);
		Shape &operator=(const Shape &sSrc) = default;
		Shape &operator=(Shape &&sSrc) = default;
		bool operator==(const std::vector<std::size_t> &sDimension);
		bool operator==(const Shape &sShape);
		bool operator!=(const std::vector<std::size_t> &sDimension);
		bool operator!=(const Shape &sShape);
		inline std::size_t operator[](std::size_t nAxis) const;

	public:
		inline std::size_t rank() const;
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
		return this->sDimension[nAxis];
	}

	inline std::size_t Shape::rank() const
	{
		return this->sDimension.size();
	}

	inline std::size_t Shape::element() const
	{
		return this->nElement;
	}
}

#endif