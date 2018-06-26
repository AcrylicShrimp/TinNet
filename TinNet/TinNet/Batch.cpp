
/*
	2018.06.24
	Created by AcrylicShrimp.
*/

#include "Batch.h"

namespace TinNet
{
	void Batch::shuffle(std::size_t nBatchSize, std::size_t nMiniBatchSize)
	{
		this->nBatch = 0;
		this->nMaxBatch = nBatchSize;
		this->nMiniBatch = nMiniBatchSize;
		this->sIndexList.resize(nBatchSize);

		if (!this->nMaxBatch)
			return;

		for (std::size_t nIndex{0}; nIndex < this->nMaxBatch; ++nIndex)
			this->sIndexList[nIndex] = nIndex;

		std::mt19937_64 sEngine{std::random_device{}()};

		for (std::size_t nIndex{0}, nMaxIndex{this->nMaxBatch - 1}; nIndex < nMaxIndex; ++nIndex)
			std::swap(this->sIndexList[nIndex], this->sIndexList[std::uniform_int_distribution<std::size_t>{nIndex + 1, nMaxIndex}(sEngine)]);
	}

	void Batch::sequential(std::size_t nBatchSize, std::size_t nMiniBatchSize)
	{
		this->nBatch = 0;
		this->nMaxBatch = nBatchSize;
		this->nMiniBatch = nMiniBatchSize;
		this->sIndexList.resize(nBatchSize);

		if (!this->nMaxBatch)
			return;

		for (std::size_t nIndex{0}; nIndex < this->nMaxBatch; ++nIndex)
			this->sIndexList[nIndex] = nIndex;
	}

	void Batch::copy(std::size_t nElementCount, const Cache sSource, Cache sDestination) const
	{
		for (std::size_t nIndex{0}, nMaxIndex{this->currentBatchSize()}; nIndex < nMaxIndex; ++nIndex)
			std::copy(sSource.cbegin() + nElementCount * this->sIndexList[this->nBatch + nIndex], sSource.cbegin() + nElementCount * (this->sIndexList[this->nBatch + nIndex] + 1), sDestination.begin());
	}

	void Batch::copy(std::size_t nElementCount, const std::vector<float> &sSource, std::vector<float> &sDestination) const
	{
		for (std::size_t nIndex{0}, nMaxIndex{this->currentBatchSize()}; nIndex < nMaxIndex; ++nIndex)
			std::copy(sSource.cbegin() + nElementCount * this->sIndexList[this->nBatch + nIndex], sSource.cbegin() + nElementCount * (this->sIndexList[this->nBatch + nIndex] + 1), sDestination.begin());
	}

	Cache Batch::obtain(std::size_t nElementCount, Cache sSource, std::size_t nBatchIndex) const
	{
		return {sSource.begin() + nElementCount * this->sIndexList[nBatchIndex], nElementCount};
	}

	std::size_t Batch::next()
	{
		std::size_t nCurrentBatchSize{this->currentBatchSize()};

		this->nBatch += this->nMiniBatch;

		return nCurrentBatchSize;
	}
}