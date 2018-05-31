
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Accessor.h"

namespace TinNet
{
	Accessor::Accessor(const Shape &sShape) :
		sShape{sShape.shrink()}
	{
		if (!sShape.element())
			throw std::invalid_argument("element cannot be zero");

		for (std::size_t nRank{0}, nMaxRank{this->sShape.rank()}; nRank < nMaxRank; ++nRank)
			this->sFactor.insert(this->sFactor.cbegin(), nRank ? this->sFactor.front() * this->sShape.size(nMaxRank - nRank) : 1);

		this->sFactor.insert(this->sFactor.cbegin(), 0);
		this->sShape = this->sShape.expand();
	}

	Accessor &Accessor::operator=(const Shape &sShape)
	{
		if (!sShape.element())
			throw std::invalid_argument("element cannot be zero");

		this->sShape = sShape.shrink();
		this->sFactor.clear();

		for (std::size_t nRank{0}, nMaxRank{this->sShape.rank()}; nRank < nMaxRank; ++nRank)
			this->sFactor.insert(this->sFactor.cbegin(), nRank ? this->sFactor.front() * this->sShape.size(nMaxRank - nRank) : 1);

		this->sFactor.insert(this->sFactor.cbegin(), 0);
		this->sShape = this->sShape.expand();

		return *this;
	}
}