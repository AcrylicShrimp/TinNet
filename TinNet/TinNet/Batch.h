
/*
	2018.06.24
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_BATCH_H

#define _CLASS_TINNET_BATCH_H

#include "TinNetDLL.h"

#include "Cache.h"

#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

namespace TinNet
{
	class TINNET_DLL Batch final
	{
	private:
		std::size_t nBatch;
		std::size_t nMaxBatch;
		std::size_t nMiniBatch;
		std::vector<std::size_t> sIndexList;

	public:
		Batch() = default;
		Batch(const Batch &sSrc) = default;
		Batch(Batch &&sSrc) = default;
		~Batch() = default;

	public:
		Batch &operator=(const Batch &sSrc) = default;
		Batch &operator=(Batch &&sSrc) = default;

	public:
		inline bool hasNext() const;
		inline std::size_t batchIndex() const;
		inline std::size_t maxBatchIndex() const;
		inline std::size_t miniBatchSize() const;
		inline std::size_t currentBatchSize() const;
		inline std::size_t shuffledIndex(std::size_t nIndex) const;
		void shuffle(std::size_t nBatchSize, std::size_t nMiniBatchSize);
		void sequential(std::size_t nBatchSize, std::size_t nMiniBatchSize);
		void copy(std::size_t nElementCount, const Cache sSource, Cache sDestination) const;
		void copy(std::size_t nElementCount, const std::vector<float> &sSource, std::vector<float> &sDestination) const;
		Cache obtain(std::size_t nElementCount, Cache sSource, std::size_t nBatchIndex) const;
		std::size_t next();
	};

	inline bool Batch::hasNext() const
	{
		return this->nBatch < this->nMaxBatch;
	}

	inline std::size_t Batch::batchIndex() const
	{
		return this->nBatch;
	}

	inline std::size_t Batch::maxBatchIndex() const
	{
		return this->nMaxBatch;
	}

	inline std::size_t Batch::miniBatchSize() const
	{
		return this->nMiniBatch;
	}

	inline std::size_t Batch::currentBatchSize() const
	{
		return this->hasNext() ? std::min(this->nMiniBatch, this->nMaxBatch - this->nBatch) : 0;
	}

	inline std::size_t Batch::shuffledIndex(std::size_t nIndex) const
	{
		return this->sIndexList[nIndex];
	}
}

#endif