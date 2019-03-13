
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#include "GEMM.h"

namespace TinNet::Compute
{
	void __vectorcall GEMM::multiply(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span sLeft, const Core::Span sRight, Core::Span sDestination) noexcept
	{
		sDestination.fillZero();

		GEMM::multiplyAdd(nMaxIndex, nRow, nColumn, sLeft, sRight, sDestination);
	}

	void __vectorcall GEMM::multiplyAdd(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span sLeft, const Core::Span sRight, Core::Span sDestination) noexcept
	{
		const auto *pL{sLeft.begin()};
		const auto *pR{sRight.begin()};
		auto *__restrict pD{sDestination.begin()};

	#pragma omp parallel for schedule(guided) default(shared) num_threads(static_cast<int>(std::max<std::size_t>(1u, std::min<std::size_t>(nMaxIndex * nRow * nColumn / 1600000u, std::thread::hardware_concurrency()))))
		for (std::int64_t nR{0}; nR < nRow; ++nR)
			for (std::size_t nC{0}; nC < nColumn; ++nC)
			{
				std::size_t nIndex{0};
				auto sSum{_mm256_setzero_ps()};

				for (; nIndex + 8 <= nMaxIndex; nIndex += 8)
					sSum = _mm256_fmadd_ps(_mm256_loadu_ps(pL + nR * nMaxIndex + nIndex), _mm256_loadu_ps(pR + nC * nMaxIndex + nIndex), sSum);

				const auto sSum128 = _mm_add_ps(_mm256_extractf128_ps(sSum, 1), _mm256_castps256_ps128(sSum));
				const auto sSum64 = _mm_add_ps(sSum128, _mm_movehl_ps(sSum128, sSum128));
				const auto sSum32 = _mm_add_ss(sSum64, _mm_shuffle_ps(sSum64, sSum64, 0x55));
				auto nSum{_mm_cvtss_f32(sSum32)};

				for (; nIndex < nMaxIndex; ++nIndex)
					nSum += pL[nR * nMaxIndex + nIndex] * pR[nC * nMaxIndex + nIndex];

				pD[nR * nColumn + nC] += nSum;
			}
	}

	void __vectorcall GEMM::dMultiplyLeft(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span sGradient, const Core::Span sRight, Core::Span sDestination) noexcept
	{
		sDestination.fillZero();

		GEMM::dMultiplyAddLeft(nMaxIndex, nRow, nColumn, sGradient, sRight, sDestination);
	}

	void __vectorcall GEMM::dMultiplyAddLeft(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span sGradient, const Core::Span sRight, Core::Span sDestination) noexcept
	{
		const auto *pG{sGradient.begin()};
		const auto *pR{sRight.begin()};
		auto *__restrict pD{sDestination.begin()};

		std::vector<float> sRightTransposed(nMaxIndex * nColumn);
		auto *__restrict pRT{sRightTransposed.data()};

	#pragma omp parallel default(shared) num_threads(static_cast<int>(std::max<std::size_t>(1u, std::min<std::size_t>(nMaxIndex * nColumn / 1600000u, std::thread::hardware_concurrency()))))
		{
		#pragma omp for schedule(guided)
			for (std::int64_t nR{0}; nR < nColumn; ++nR)
				for (std::size_t nC{0}; nC < nMaxIndex; ++nC)
					pRT[nC * nColumn + nR] = pR[nR * nMaxIndex + nC];

		#pragma omp for schedule(guided)
			for (std::int64_t nR{0}; nR < nRow; ++nR)
			{
				for (std::size_t nC{0}; nC < nMaxIndex; ++nC)
				{
					std::size_t nIndex{0};
					auto sSum{_mm256_setzero_ps()};

					for (; nIndex + 8 <= nColumn; nIndex += 8)
						sSum = _mm256_fmadd_ps(_mm256_loadu_ps(pG + nR * nColumn + nIndex), _mm256_loadu_ps(pR + nC * nColumn + nIndex), sSum);

					const auto sSum128 = _mm_add_ps(_mm256_extractf128_ps(sSum, 1), _mm256_castps256_ps128(sSum));
					const auto sSum64 = _mm_add_ps(sSum128, _mm_movehl_ps(sSum128, sSum128));
					const auto sSum32 = _mm_add_ss(sSum64, _mm_shuffle_ps(sSum64, sSum64, 0x55));
					auto nSum{_mm_cvtss_f32(sSum32)};

					for (; nIndex < nColumn; ++nIndex)
						nSum += pG[nR * nColumn + nIndex] * pR[nC * nColumn + nIndex];

					pD[nR * nMaxIndex + nC] += nSum;
				}
			}
		}
	}

	void __vectorcall GEMM::dMultiplyRight(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span sGradient, const Core::Span sLeft, Core::Span sDestination) noexcept
	{
		sDestination.fillZero();

		GEMM::dMultiplyAddRight(nMaxIndex, nRow, nColumn, sGradient, sLeft, sDestination);
	}

	void __vectorcall GEMM::dMultiplyAddRight(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span sGradient, const Core::Span sLeft, Core::Span sDestination) noexcept
	{
		const auto *pG{sGradient.begin()};
		const auto *pL{sLeft.begin()};
		auto *__restrict pD{sDestination.begin()};

		std::vector<float> sGradientTransposed(nRow * nColumn);
		std::vector<float> sLeftTransposed(nRow * nMaxIndex);
		auto *__restrict pGT{sGradientTransposed.data()};
		auto *__restrict pLT{sLeftTransposed.data()};

	#pragma omp parallel default(shared) num_threads(static_cast<int>(std::max<std::size_t>(1u, std::min<std::size_t>(nMaxIndex * nRow * nColumn / 1600000u, std::thread::hardware_concurrency()))))
		{
		#pragma omp for schedule(guided) nowait
			for (std::int64_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC)
					pGT[nC * nRow + nR] = pG[nR * nColumn + nC];

		#pragma omp for schedule(guided)
			for (std::int64_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nMaxIndex; ++nC)
					pLT[nC * nRow + nR] = pL[nR * nMaxIndex + nC];

		#pragma omp for schedule(guided)
			for (std::int64_t nR{0}; nR < nColumn; ++nR)
				for (std::size_t nC{0}; nC < nMaxIndex; ++nC)
				{
					std::size_t nIndex{0};
					auto sSum{_mm256_setzero_ps()};

					for (; nIndex + 8 <= nRow; nIndex += 8)
						sSum = _mm256_fmadd_ps(_mm256_loadu_ps(pGT + nR * nRow + nIndex), _mm256_loadu_ps(pLT + nC * nRow + nIndex), sSum);

					const auto sSum128 = _mm_add_ps(_mm256_extractf128_ps(sSum, 1), _mm256_castps256_ps128(sSum));
					const auto sSum64 = _mm_add_ps(sSum128, _mm_movehl_ps(sSum128, sSum128));
					const auto sSum32 = _mm_add_ss(sSum64, _mm_shuffle_ps(sSum64, sSum64, 0x55));
					auto nSum{_mm_cvtss_f32(sSum32)};

					for (; nIndex < nRow; ++nIndex)
						nSum += pGT[nR * nRow + nIndex] * pLT[nC * nRow + nIndex];

					pD[nR * nMaxIndex + nC] += nSum;
				}
		}
	}
}