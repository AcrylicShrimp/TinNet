
/*
	2018.10.15
	Created by AcrylicShrimp.
*/

#include "Shape.h"

namespace TinNet::Core
{
	Shape::Shape()
	{
		this->sDimension.reserve(4);
	}

	Shape::Shape(std::initializer_list<std::size_t> sDimension) :
		Shape(sDimension.begin(), sDimension.end())
	{
		//Empty.
	}

	Shape &Shape::operator=(std::initializer_list<std::size_t> sDimension)
	{
		this->assign(sDimension.begin(), sDimension.end());

		return *this;
	}

	bool Shape::operator==(std::initializer_list<std::size_t> sDimension) const
	{
		return this->equals(sDimension.begin(), sDimension.end());
	}

	bool Shape::operator==(const Shape &sShape) const
	{
		return this->equals(sShape.sDimension.cbegin(), sShape.sDimension.cend());
	}

	bool Shape::operator!=(std::initializer_list<std::size_t> sDimension) const
	{
		return !this->operator==(sDimension);
	}

	bool Shape::operator!=(const Shape &sShape) const
	{
		return !this->operator==(sShape);
	}

	Shape Shape::expand() const
	{
		auto sResult{*this};

		sResult.sDimension.emplace_back(1);

		return sResult;
	}

	Shape Shape::expand(std::size_t nRank) const
	{
		auto sResult{*this};

		if (nRank < this->rank())
			return sResult;

		for (std::size_t nR{this->rank()}; nR < nRank; ++nR)
			sResult.sDimension.emplace_back(1);

		return sResult;
	}

	Shape Shape::shrink() const
	{
		auto sResult{*this};

		while (!sResult.sDimension.empty() && sResult.sDimension.back() == 1)
			sResult.sDimension.pop_back();

		return sResult;
	}

	Shape Shape::squeeze() const
	{
		Shape sResult;

		for (auto nSize : this->sDimension)
			if (nSize != 1)
				sResult.sDimension.emplace_back(nSize);

		return sResult;
	}

	Shape Shape::broadcast(const Shape &sLeft, const Shape &sRight)
	{
		if (!sLeft.rank() && !sRight.rank())
			return Shape{};

		Shape sResult;
		std::size_t nAxis{0};

		for (auto nMinAxis{std::min(sLeft.rank(), sRight.rank())}; nAxis < nMinAxis; ++nAxis)
		{
			if (sLeft[nAxis] != sRight[nAxis] && sLeft[nAxis] != 1 && sRight[nAxis] != 1)
				throw std::invalid_argument("cannot broadcast");

			sResult.sDimension.emplace_back(std::max(sLeft[nAxis], sRight[nAxis]));
		}

		for (auto nMaxAxis{std::max(sLeft.rank(), sRight.rank())}; nAxis < nMaxAxis; ++nAxis)
			sResult.sDimension.emplace_back((nAxis < sLeft.rank() ? sLeft : sRight)[nAxis]);

		return sResult;
	}
}