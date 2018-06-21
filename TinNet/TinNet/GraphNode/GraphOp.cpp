
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "GraphOp.h"

namespace TinNet::GraphNode
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

	void GraphOp::dMatmulAccumulateLeft(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
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

					sDestination[nIndex1 + nR * nColumn + nC] += nValue;
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

	void GraphOp::dMatmulAccumulateRight(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
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

					sDestination[nIndex2 + nR * nColumn + nC] += nValue;
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

	void GraphOp::matmulTransposedAVX(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;
			float vTemp[8] alignas(256);

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nValue{_mm256_setzero_ps()};

					for (nIndex = 0; nIndex + 8 <= nMaxIndex; nIndex += 8)
						nValue = _mm256_add_ps(nValue, _mm256_mul_ps(_mm256_loadu_ps(&sLeft[nIndex1 + nR * nMaxIndex + nIndex]), _mm256_loadu_ps(&sRight[nIndex2 + nC * nMaxIndex + nIndex])));

					_mm256_store_ps(vTemp, nValue);

					vTemp[0] += vTemp[1] + vTemp[2] + vTemp[3] + vTemp[4] + vTemp[5] + vTemp[6] + vTemp[7];

					for (; nIndex < nMaxIndex; ++nIndex)
						vTemp[0] += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nC * nMaxIndex + nIndex];

					sDestination[nIndex0 + nR * nColumn + nC] = vTemp[0];
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

	void GraphOp::matmulAccumulateTransposedAVX(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fMatMul = [nRow, nColumn, nMaxIndex, &sLeft, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;
			float vTemp[8] alignas(256);

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					auto nValue{_mm256_setzero_ps()};

					for (nIndex = 0; nIndex + 8 <= nMaxIndex; nIndex += 8)
						nValue = _mm256_add_ps(nValue, _mm256_mul_ps(_mm256_loadu_ps(&sLeft[nIndex1 + nR * nMaxIndex + nIndex]), _mm256_loadu_ps(&sRight[nIndex2 + nC * nMaxIndex + nIndex])));

					_mm256_store_ps(vTemp, nValue);

					vTemp[0] += vTemp[1] + vTemp[2] + vTemp[3] + vTemp[4] + vTemp[5] + vTemp[6] + vTemp[7];

					for (; nIndex < nMaxIndex; ++nIndex)
						vTemp[0] += sLeft[nIndex1 + nR * nMaxIndex + nIndex] * sRight[nIndex2 + nC * nMaxIndex + nIndex];

					sDestination[nIndex0 + nR * nColumn + nC] += vTemp[0];
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

	void GraphOp::dMatmulLeftTransposedAVX(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		sDestination.zero();

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					const float nBackward{sBackward[nIndex0 + nR * nColumn + nC]};
					const auto nBackwardM256{_mm256_set1_ps(nBackward)};

					for (nIndex = 0; nIndex + 8 <= nMaxIndex; nIndex += 8)
					{
						float *__restrict pDestination{&sDestination[nIndex1 + nR * nMaxIndex + nIndex]};
						_mm256_storeu_ps(pDestination, _mm256_add_ps(_mm256_loadu_ps(pDestination), _mm256_mul_ps(nBackwardM256, _mm256_loadu_ps(&sRight[nIndex2 + nC * nMaxIndex + nIndex]))));
					}

					for (; nIndex < nMaxIndex; ++nIndex)
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

	void GraphOp::dMatmulAccumulateLeftTransposedAVX(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sRight, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					const float nBackward{sBackward[nIndex0 + nR * nColumn + nC]};
					const auto nBackwardM256{_mm256_set1_ps(nBackward)};

					for (nIndex = 0; nIndex + 8 <= nMaxIndex; nIndex += 8)
					{
						float *__restrict pDestination{&sDestination[nIndex1 + nR * nMaxIndex + nIndex]};
						_mm256_storeu_ps(pDestination, _mm256_add_ps(_mm256_loadu_ps(pDestination), _mm256_mul_ps(nBackwardM256, _mm256_loadu_ps(&sRight[nIndex2 + nC * nMaxIndex + nIndex]))));
					}

					for (; nIndex < nMaxIndex; ++nIndex)
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

	void GraphOp::dMatmulRightTransposedAVX(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		sDestination.zero();

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sLeft, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					const float nBackward{sBackward[nIndex0 + nR * nColumn + nC]};
					const auto nBackwardM256{_mm256_set1_ps(nBackward)};

					for (nIndex = 0; nIndex + 8 <= nMaxIndex; nIndex += 8)
					{
						float *__restrict pDestination{&sDestination[nIndex2 + nC * nMaxIndex + nIndex]};
						_mm256_storeu_ps(pDestination, _mm256_add_ps(_mm256_loadu_ps(pDestination), _mm256_mul_ps(nBackwardM256, _mm256_loadu_ps(&sLeft[nIndex1 + nR * nMaxIndex + nIndex]))));
					}

					for (; nIndex < nMaxIndex; ++nIndex)
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

	void GraphOp::dMatmulAccumulateRightTransposedAVX(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		auto nRow{sLeftShape[sLeftShape.rank() - 2]};
		auto nColumn{sRightShape[sRightShape.rank() - 1]};
		auto nMaxIndex{sLeftShape[sLeftShape.rank() - 1]};

		auto fDMatMul = [nRow, nColumn, nMaxIndex, &sBackward, &sLeft, &sDestination](std::size_t nIndex0, std::size_t nIndex1, std::size_t nIndex2)
		{
			std::size_t nIndex;

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
				{
					const float nBackward{sBackward[nIndex0 + nR * nColumn + nC]};
					const auto nBackwardM256{_mm256_set1_ps(nBackward)};

					for (nIndex = 0; nIndex + 8 <= nMaxIndex; nIndex += 8)
					{
						float *__restrict pDestination{&sDestination[nIndex2 + nC * nMaxIndex + nIndex]};
						_mm256_storeu_ps(pDestination, _mm256_add_ps(_mm256_loadu_ps(pDestination), _mm256_mul_ps(nBackwardM256, _mm256_loadu_ps(&sLeft[nIndex1 + nR * nMaxIndex + nIndex]))));
					}

					for (; nIndex < nMaxIndex; ++nIndex)
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
}