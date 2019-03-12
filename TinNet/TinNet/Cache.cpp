
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "Cache.h"

namespace TinNet
{
	Cache::Cache() :
		pBase{nullptr},
		nSize{0}
	{
		//Empty.
	}

	Cache::Cache(std::vector<float> &sVector) :
		Cache(sVector.data(), sVector.size())
	{
		//Empty.
	}

	Cache::Cache(float *pBase, const float *pEnd) :
		Cache(pBase, static_cast<std::size_t>(pEnd - pBase))
	{
		//Empty.
	}

	Cache::Cache(float *pBase, std::size_t nSize) :
		pBase{pBase},
		nSize{nSize}
	{
		//Empty.
	}

	Cache::Cache(const Cache &sSrc) :
		pBase{sSrc.pBase},
		nSize{sSrc.nSize}
	{
		//Empty.
	}

	Cache &Cache::operator=(const Cache &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->pBase = sSrc.pBase;
		this->nSize = sSrc.nSize;

		return *this;
	}

	Cache &Cache::operator=(std::vector<float> &sVector)
	{
		this->pBase = sVector.data();
		this->nSize = sVector.size();

		return *this;
	}

	void Cache::zero()
	{
		std::fill(this->pBase, this->pBase + this->nSize, .0f);
	}

	void Cache::one()
	{
		std::fill(this->pBase, this->pBase + this->nSize, 1.f);
	}

	void Cache::fill(float nValue)
	{
		std::fill(this->pBase, this->pBase + this->nSize, nValue);
	}

	void Cache::copy(Cache sCache)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBase[nIndex] = sCache.pBase[nIndex];
	}

	void Cache::copy(Cache sCache, float nFactor)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBase[nIndex] = nFactor * sCache.pBase[nIndex];
	}

	void Cache::copyNegative(Cache sCache)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBase[nIndex] = -sCache.pBase[nIndex];
	}

	float Cache::accumulate() const
	{
		return std::accumulate(this->pBase, this->pBase + this->nSize, .0f);
	}

	void Cache::accumulate(Cache sCache)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBase[nIndex] += sCache.pBase[nIndex];
	}

	void Cache::accumulate(Cache sCache, float nFactor)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBase[nIndex] += nFactor * sCache.pBase[nIndex];
	}
	
	std::string Cache::toString() const
	{
		std::ostringstream sStream;
		sStream << "[";

		for (std::size_t nIndex{0}; nIndex < this->nSize; )
		{
			sStream << this->pBase[nIndex];

			if (++nIndex != this->nSize)
				sStream << ", ";
		}

		sStream << "]";
		return sStream.str();
	}

	std::string Cache::toString(std::size_t nMaxIndex) const
	{
		nMaxIndex = std::min(nMaxIndex, this->nSize);

		std::ostringstream sStream;
		sStream << "[";

		for (std::size_t nIndex{0}; nIndex < nMaxIndex; )
		{
			sStream << this->pBase[nIndex];

			if (++nIndex != nMaxIndex)
				sStream << ", ";
		}

		sStream << "]";
		return sStream.str();
	}
}