
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#include "GraphOp.h"

namespace TinNet::Graph
{
	void GraphOp::matmul(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto &nDestination{sDestination[nIndex0 + nR * nColumn + nC] = .0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nDestination += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nIndex * nColumn + nC];
				}
		};

		if (sLeftShape.rank() <= 2 || sLeftShape[sLeftShape.rank() - 3] == 1)
		{
			fMatMul(0, 0, 0);
			return;
		}

		for (sIterator.prepare(2); sIterator; ++sIterator)
			fMatMul(sIterator.index<0>(), sIterator.index<1>(), sIterator.index<2>());
	}

	void GraphOp::dMatmulLeft(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sLeftShape[sLeftShape.rank() - 1]};
		auto nMaxIndex{sRightShape[sRightShape.rank() - 1]};

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto &nDestination{sDestination[nIndex1 + nR * nColumn + nC] = .0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nDestination += sRight[nIndex2 + nC * nMaxIndex + nIndex] * sBackward[nIndex0 + nR * nMaxIndex + nIndex];
				}
		};

		if (sLeftShape.rank() <= 2 || sLeftShape[sLeftShape.rank() - 3] == 1)
		{
			fDMatMul(0, 0, 0);
			return;
		}

		for (sIterator.prepare(2); sIterator; ++sIterator)
			fDMatMul(sIterator.index<0>(), sIterator.index<1>(), sIterator.index<2>());
	}

	void GraphOp::dMatmulRight(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sRightShape[sRightShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 2]};

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sLeft, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto &nDestination{sDestination[nIndex2 + nR * nColumn + nC] = .0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nDestination += sLeft[nIndex1 + nIndex * nRow + nR] * sBackward[nIndex0 + nIndex * nColumn + nC];
				}
		};

		if (sLeftShape.rank() <= 2 || sLeftShape[sLeftShape.rank() - 3] == 1)
		{
			fDMatMul(0, 0, 0);
			return;
		}

		for (sIterator.prepare(2); sIterator; ++sIterator)
			fDMatMul(sIterator.index<0>(), sIterator.index<1>(), sIterator.index<2>());
	}
}