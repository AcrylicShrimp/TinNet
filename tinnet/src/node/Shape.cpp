
#include "tinnet/includes/node/Shape.h"

#include <algorithm>
#include <stdexcept>

namespace tinnet::node {
	Shape::Shape()
	{
		this->sDimension.reserve(4);
	}

	Shape::Shape(const std::vector<std::size_t> &sRhs) : sDimension{sRhs.cbegin(), sRhs.cend()} {}

	Shape::Shape(std::vector<std::size_t> &&sRhs) noexcept : sDimension{std::move(sRhs)} {}

	Shape &Shape::operator=(const std::vector<std::size_t> &sRhs)
	{
		this->sDimension = sRhs;
		return *this;
	}

	Shape &Shape::operator=(std::vector<std::size_t> &&sRhs) noexcept
	{
		this->sDimension = std::move(sRhs);
		return *this;
	}

	bool Shape::operator==(const Shape &sRhs) const
	{
		return this->sDimension == sRhs.sDimension;
	}

	bool operator==(const Shape &sLhs, const std::vector<std::size_t> &sRhs)
	{
		return sLhs.sDimension == sRhs;
	}

	bool operator==(const std::vector<std::size_t> &sLhs, const Shape &sRhs)
	{
		return sLhs == sRhs.sDimension;
	}

	bool Shape::operator!=(const Shape &sRhs) const
	{
		return this->sDimension != sRhs.sDimension;
	}

	bool operator!=(const Shape &sLhs, const std::vector<std::size_t> &sRhs)
	{
		return sLhs.sDimension != sRhs;
	}

	bool operator!=(const std::vector<std::size_t> &sLhs, const Shape &sRhs)
	{
		return sLhs != sRhs.sDimension;
	}

	std::ostream &operator<<(std::ostream &sLhs, const Shape &sRhs)
	{
		sLhs << "[";

		for (std::size_t nIndex{0}, nMaxIndex{sRhs.sDimension.size()}; nIndex < nMaxIndex; ++nIndex) {
			sLhs << sRhs.sDimension[nIndex];

			if (nIndex + 1 != nMaxIndex) sLhs << ", ";
		}

		return sLhs << "]";
	}

	Shape Shape::extend() const
	{
		auto sResult{*this};
		sResult.sDimension.insert(sResult.sDimension.cbegin(), 1);

		return sResult;
	}

	Shape Shape::extend(std::size_t nRank) const
	{
		auto sResult{*this};

		while (sResult.rank() < nRank) sResult.sDimension.insert(sResult.sDimension.cbegin(), 1);

		return sResult;
	}

	Shape Shape::shrink() const
	{
		auto sResult{*this};

		while (!sResult.sDimension.empty() && sResult.sDimension.front() == 1)
			sResult.sDimension.erase(sResult.sDimension.cbegin());

		return sResult;
	}

	Shape Shape::squeeze() const
	{
		Shape sResult;

		for (auto nSize: this->sDimension)
			if (nSize != 1) sResult.sDimension.emplace_back(nSize);

		return sResult;
	}

	Shape Shape::broadcast(const Shape &sLhs, const Shape &sRhs)
	{
		Shape sResult;

		auto iL{sLhs.sDimension.crbegin()}, iLEnd{sLhs.sDimension.crend()}, iR{sRhs.sDimension.crbegin()},
			iREnd{sRhs.sDimension.crend()};

		// TODO: Add special case handling - dimension contains 0 - here.

		for (; iL != iLEnd && iR != iREnd; ++iL, ++iR) {
			if (*iL != *iR && *iL != 1 && *iR != 1) throw std::runtime_error{"unable to broadcast"};

			sResult.sDimension.insert(sResult.sDimension.cbegin(), std::max(*iL, *iR));
		}

		if (iL != iLEnd)
			for (; iL != iLEnd; ++iL) sResult.sDimension.insert(sResult.sDimension.cbegin(), *iL);
		else if (iR != iREnd)
			for (; iR != iREnd; ++iR) sResult.sDimension.insert(sResult.sDimension.cbegin(), *iR);

		return sResult;
	}
}	 // namespace tinnet::node