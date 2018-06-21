
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "Cache.h"

namespace TinNet
{
	Cache::Cache() :
		pBegin{nullptr},
		nSize{0}
	{
		//Empty.
	}

	Cache::Cache(std::vector<float> &sVector) :
		Cache(sVector.data(), sVector.size())
	{
		//Empty.
	}

	Cache::Cache(float *pBegin, const float *pEnd) :
		Cache(pBegin, static_cast<std::size_t>(pEnd - pBegin))
	{
		//Empty.
	}

	Cache::Cache(float *pBegin, std::size_t nSize) :
		pBegin{pBegin},
		nSize{nSize}
	{
		//Empty.
	}

	Cache::Cache(const Cache &sSrc) :
		pBegin{sSrc.pBegin},
		nSize{sSrc.nSize}
	{
		//Empty.
	}

	Cache &Cache::operator=(const Cache &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->pBegin = sSrc.pBegin;
		this->nSize = sSrc.nSize;

		return *this;
	}

	Cache &Cache::operator=(std::vector<float> &sVector)
	{
		this->pBegin = sVector.data();
		this->nSize = sVector.size();

		return *this;
	}

	void Cache::zero()
	{
		std::fill(this->pBegin, this->pBegin + this->nSize, .0f);
	}

	void Cache::one()
	{
		std::fill(this->pBegin, this->pBegin + this->nSize, 1.f);
	}

	void Cache::fill(float nValue)
	{
		std::fill(this->pBegin, this->pBegin + this->nSize, nValue);
	}

	void Cache::copy(Cache sCache)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBegin[nIndex] = sCache.pBegin[nIndex];
	}

	void Cache::copy(Cache sCache, float nFactor)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBegin[nIndex] = nFactor * sCache.pBegin[nIndex];
	}

	void Cache::copyNegative(Cache sCache)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBegin[nIndex] = -sCache.pBegin[nIndex];
	}

	float Cache::accumulate() const
	{
		return std::accumulate(this->pBegin, this->pBegin + this->nSize, .0f);
	}

	void Cache::accumulate(Cache sCache)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBegin[nIndex] += sCache.pBegin[nIndex];
	}

	void Cache::accumulate(Cache sCache, float nFactor)
	{
		for (std::size_t nIndex{0}, nSize{std::min(this->nSize, sCache.nSize)}; nIndex < nSize; ++nIndex)
			this->pBegin[nIndex] += nFactor * sCache.pBegin[nIndex];
	}
	
	std::string Cache::toString() const
	{
		std::ostringstream sStream;
		sStream << "[";

		for (std::size_t nIndex{0}; nIndex < this->nSize; )
		{
			sStream << this->pBegin[nIndex];

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
			sStream << this->pBegin[nIndex];

			if (++nIndex != nMaxIndex)
				sStream << ", ";
		}

		sStream << "]";
		return sStream.str();
	}
}