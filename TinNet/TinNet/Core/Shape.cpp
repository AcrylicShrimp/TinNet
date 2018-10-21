
/*
	2018.10.15
	Created by AcrylicShrimp.
*/

#include "Shape.h"

namespace TinNet::Core
{
	Shape::Shape() :
		nElement{1}
	{
		//Empty.
	}

	Shape::Shape(const std::vector<std::size_t> &sDimension) :
		nElement{1},
		sDimension(sDimension)
	{
		for (auto nSize : this->sDimension)
			nElement *= nSize;
	}

	Shape::Shape(std::vector<std::size_t> &&sDimension) :
		nElement{1},
		sDimension(std::move(sDimension))
	{
		for (auto nSize : this->sDimension)
			nElement *= nSize;
	}

	Shape &Shape::operator=(const std::vector<std::size_t> &sDimension)
	{
		this->nElement = 1;
		this->sDimension = sDimension;

		for (auto nSize : this->sDimension)
			nElement *= nSize;

		return *this;
	}

	Shape &Shape::operator=(std::vector<std::size_t> &&sDimension)
	{
		this->nElement = 1;
		this->sDimension = std::move(sDimension);

		for (auto nSize : this->sDimension)
			nElement *= nSize;

		return *this;
	}

	bool Shape::operator==(const std::vector<std::size_t> &sDimension)
	{
		if (this->rank() != sDimension.size())
			return false;

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sDimension[nAxis] != sDimension[nAxis])
				return false;

		return true;
	}

	bool Shape::operator==(const Shape &sShape)
	{
		if (this->nElement != sShape.nElement || this->rank() != sShape.rank())
			return false;

		for (std::size_t nAxis{0}, nMaxAxis{this->rank()}; nAxis < nMaxAxis; ++nAxis)
			if (this->sDimension[nAxis] != sShape.sDimension[nAxis])
				return false;

		return true;
	}

	bool Shape::operator!=(const std::vector<std::size_t> &sDimension)
	{
		return !this->operator==(sDimension);
	}

	bool Shape::operator!=(const Shape &sShape)
	{
		return !this->operator==(sShape);
	}

	Shape Shape::shrink() const
	{
		auto sResult{*this};

		while (!sResult.sDimension.empty() && sResult.sDimension.front() == 1)
			sResult.sDimension.erase(sResult.sDimension.begin());

		return sResult;
	}

	Shape Shape::expand() const
	{
		Shape sResult{*this};

		sResult.sDimension.insert(sResult.sDimension.cbegin(), 1);

		return sResult;
	}

	Shape Shape::expand(std::size_t nRank) const
	{
		Shape sResult{*this};

		if (nRank < this->rank())
			return sResult;

		for (std::size_t nR{this->rank()}; nR < nRank; ++nR)
			sResult.sDimension.insert(sResult.sDimension.cbegin(), 1);

		return sResult;
	}

	Shape Shape::squeeze() const
	{
		std::vector<std::size_t> sResult;

		for (auto nSize : this->sDimension)
		{
			if (nSize == 1)
				continue;

			sResult.emplace_back(nSize);
		}

		return Shape{sResult};
	}

	void Shape::set(std::size_t nAxis, std::size_t nSize)
	{
		if (nAxis >= this->sDimension.size())
			return;

		this->sDimension[nAxis] = nSize;
		this->nElement = 1;

		for (auto nSize : this->sDimension)
			nElement *= nSize;
	}

	Shape Shape::broadcast(const Shape &sLeft, const Shape &sRight)
	{
		if (!sLeft.element() || !sRight.element())
			throw std::invalid_argument("element cannot be zero");

		if (!sLeft.rank() && !sRight.rank())
			return {};

		std::vector<std::size_t> sShape;
		std::size_t nAxis{std::max(sLeft.rank(), sRight.rank()) - 1};
		auto sExpandedLeft{sLeft.expand(nAxis + 1)};
		auto sExpandedRight{sRight.expand(nAxis + 1)};

		do
		{
			if (sExpandedLeft[nAxis] != sExpandedRight[nAxis] && (sExpandedLeft[nAxis] != 1 && sExpandedRight[nAxis] != 1))
				throw std::invalid_argument("cannot broadcast");

			sShape.insert(sShape.cbegin(), std::max(sExpandedLeft[nAxis], sExpandedRight[nAxis]));
		}
		while (nAxis--);

		return {std::move(sShape)};
	}
}