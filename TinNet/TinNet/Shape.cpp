
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Shape.h"

namespace TinNet
{
	Shape::Shape() :
		nElement{1}
	{
		//Empty.
	}

	Shape::Shape(std::initializer_list<std::size_t> sShape) :
		nElement{1},
		sShape(sShape)
	{
		for (auto nSize : this->sShape)
			nElement *= nSize;
	}

	Shape::Shape(const std::vector<std::size_t> &sShape) :
		nElement{1},
		sShape(sShape)
	{
		for (auto nSize : this->sShape)
			nElement *= nSize;
	}

	Shape::Shape(std::vector<std::size_t> &&sShape) :
		nElement{1},
		sShape(std::move(sShape))
	{
		for (auto nSize : this->sShape)
			nElement *= nSize;
	}

	Shape &Shape::operator=(std::initializer_list<std::size_t> sShape)
	{
		this->nElement = 1;
		this->sShape = sShape;

		for (auto nSize : this->sShape)
			nElement *= nSize;

		return *this;
	}

	Shape &Shape::operator=(const std::vector<std::size_t> &sShape)
	{
		this->nElement = 1;
		this->sShape = sShape;

		for (auto nSize : this->sShape)
			nElement *= nSize;

		return *this;
	}

	bool Shape::operator==(std::initializer_list<std::size_t> sShape) const
	{
		if (this->rank() != sShape.size())
			return false;

		auto pShape{sShape.begin()};

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sShape[nAxis] != *pShape++)
				return false;

		return true;
	}

	bool Shape::operator==(const std::vector<std::size_t> &sShape) const
	{
		if (this->rank() != sShape.size())
			return false;

		auto pShape{sShape.data()};

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sShape[nAxis] != *pShape++)
				return false;

		return true;
	}

	bool Shape::operator==(const Shape &sShape) const
	{
		if (this->rank() != sShape.rank())
			return false;

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sShape[nAxis] != sShape.sShape[nAxis])
				return false;

		return true;
	}

	bool Shape::operator!=(std::initializer_list<std::size_t> sShape) const
	{
		if (this->rank() != sShape.size())
			return true;

		auto pShape{sShape.begin()};

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sShape[nAxis] != *pShape++)
				return true;

		return false;
	}

	bool Shape::operator!=(const std::vector<std::size_t> &sShape) const
	{
		if (this->rank() != sShape.size())
			return true;

		auto pShape{sShape.data()};

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sShape[nAxis] != *pShape++)
				return true;

		return false;
	}

	bool Shape::operator!=(const Shape &sShape) const
	{
		if (this->rank() != sShape.rank())
			return true;

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sShape[nAxis] != sShape.sShape[nAxis])
				return true;

		return false;
	}

	Shape Shape::shrink() const
	{
		Shape sResult{*this};

		while (!sResult.sShape.empty() && sResult.sShape.front() == 1)
			sResult.sShape.erase(sResult.sShape.begin());

		return sResult;
	}

	Shape Shape::expand() const
	{
		Shape sResult{*this};

		sResult.sShape.insert(sResult.sShape.cbegin(), 1);

		return sResult;
	}

	Shape Shape::expand(std::size_t nRank) const
	{
		if (nRank < this->rank())
			throw std::invalid_argument("rank is too small");

		Shape sResult{*this};

		for (std::size_t nR{this->rank()}; nR < nRank; ++nR)
			sResult.sShape.insert(sResult.sShape.cbegin(), 1);

		return sResult;
	}

	Shape Shape::squeeze() const
	{
		std::vector<std::size_t> sResult;

		for (auto nSize : this->sShape)
		{
			if (nSize == 1)
				continue;

			sResult.emplace_back(nSize);
		}

		return Shape{sResult};
	}

	void Shape::set(std::size_t nAxis, std::size_t nSize)
	{
		if (nAxis >= this->sShape.size())
			return;

		this->sShape[nAxis] = nSize;
		this->nElement = 1;

		for (auto nSize : this->sShape)
			nElement *= nSize;
	}

	Shape Shape::broadcast(const Shape &sLeft, const Shape &sRight)
	{
		if (!sLeft.element() || !sRight.element())
			throw std::invalid_argument("element cannot be zero");

		if (!sLeft.rank() && !sRight.rank())
			return Shape{};

		std::vector<std::size_t> sShape;
		std::size_t nAxis{std::max(sLeft.rank(), sRight.rank()) - 1};
		auto sExpandedLeft{sLeft.expand(nAxis + 1)};
		auto sExpandedRight{sRight.expand(nAxis + 1)};

		do
		{
			if (sExpandedLeft.size(nAxis) != sExpandedRight.size(nAxis) && (sExpandedLeft.size(nAxis) != 1 && sExpandedRight.size(nAxis) != 1))
				throw std::invalid_argument("cannot broadcast");

			sShape.insert(sShape.cbegin(), std::max(sExpandedLeft.size(nAxis), sExpandedRight.size(nAxis)));
		} while (nAxis--);

		return Shape{std::move(sShape)};
	}
}