
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
					auto nValue{.0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nValue += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nIndex * nColumn + nC];

					sDestination[nIndex0 + nR * nColumn + nC] = nValue;
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

	void GraphOp::matmulAccumulate(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nValue{.0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nValue += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nIndex * nColumn + nC];

					sDestination[nIndex0 + nR * nColumn + nC] += nValue;
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
					auto nValue{.0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nValue += sRight[nIndex2 + nC * nMaxIndex + nIndex] * sBackward[nIndex0 + nR * nMaxIndex + nIndex];

					sDestination[nIndex1 + nR * nColumn + nC] = nValue;
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
					auto nValue{.0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nValue += sLeft[nIndex1 + nIndex * nRow + nR] * sBackward[nIndex0 + nIndex * nColumn + nC];

					sDestination[nIndex2 + nR * nColumn + nC] = nValue;
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

	void GraphOp::matmulTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nValue{.0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nValue += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nC * nMaxIndex + nIndex];

					sDestination[nIndex0 + nR * nColumn + nC] = nValue;
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

	void GraphOp::matmulAccumulateTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nValue{.0f};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						nValue += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nC * nMaxIndex + nIndex];

					sDestination[nIndex0 + nR * nColumn + nC] += nValue;
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

	void GraphOp::dMatmulLeftTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		sDestination.zero();

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nBackward{sBackward[nIndex0 + nR * nColumn + nC]};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						sDestination[nIndex1 + nR * nMaxIndex + nIndex] += sRight[nIndex2 + nC * nMaxIndex + nIndex] * nBackward;
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

	void GraphOp::dMatmulRightTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		sDestination.zero();

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sLeft, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nBackward{sBackward[nIndex0 + nR * nColumn + nC]};

					for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex)
						sDestination[nIndex2 + nC * nMaxIndex + nIndex] += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * nBackward;
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

	void GraphOp::matmulTransposedSIMD(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nValue{_mm_setzero_ps()};

					for (nIndex = 0; nIndex + 4 < nMaxIndex; nIndex += 4)
						nValue = _mm_add_ps(nValue, _mm_mul_ps(_mm_loadu_ps(&sLeft[nIndex1 + nR * nMaxIndex + nIndex]), _mm_loadu_ps(&sRight[nIndex2 + nC * nMaxIndex + nIndex])));

					nValue = _mm_hadd_ps(nValue, nValue);
					nValue = _mm_hadd_ps(nValue, nValue);

					float nTemp;
					_mm_store_ss(&nTemp, nValue);

					for (; nIndex < nMaxIndex; ++nIndex)
						nTemp += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nC * nMaxIndex + nIndex];

					sDestination[nIndex0 + nR * nColumn + nC] = nTemp;
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

	void GraphOp::matmulAccumulateTransposedSIMD(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nValue{_mm_setzero_ps()};

					for (nIndex = 0; nIndex + 4 < nMaxIndex; nIndex += 4)
						nValue = _mm_add_ps(nValue, _mm_mul_ps(_mm_loadu_ps(&sLeft[nIndex1 + nR * nMaxIndex + nIndex]), _mm_loadu_ps(&sRight[nIndex2 + nC * nMaxIndex + nIndex])));

					nValue = _mm_hadd_ps(nValue, nValue);
					nValue = _mm_hadd_ps(nValue, nValue);

					float nTemp;
					_mm_store_ss(&nTemp, nValue);

					for (; nIndex < nMaxIndex; ++nIndex)
						nTemp += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nC * nMaxIndex + nIndex];

					sDestination[nIndex0 + nR * nColumn + nC] += nTemp;
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
}