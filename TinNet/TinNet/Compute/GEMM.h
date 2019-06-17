
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_COMPUTE_GEMM_H

#define _CLASS_TINNET_COMPUTE_GEMM_H

#include "../TinNetDLL.h"

#include "../Core/Span.h"	//TinNet::Core::Span

#include <algorithm>		//std::min, std::max
#include <cstddef>			//std::size_t
#include <immintrin.h>		//AVX2
#include <thread>			//std::thread::hardware_concurrency
#include <vector>			//std::vector

namespace TinNet::Compute
{
	class TINNET_DLL GEMM final
	{
	public:
		GEMM() = delete;
		GEMM(const GEMM &sSrc) = delete;
		~GEMM() = delete;

	public:
		GEMM &operator=(const GEMM &sSrc) = delete;

	public:
		static void __vectorcall multiply(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span<float> sLeft, const Core::Span<float> sRight, Core::Span<float> sDestination) noexcept;
		static void __vectorcall multiplyAdd(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span<float> sLeft, const Core::Span<float> sRight, Core::Span<float> sDestination) noexcept;

		static void __vectorcall dMultiplyLeft(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span<float> sGradient, const Core::Span<float> sRight, Core::Span<float> sDestination) noexcept;
		static void __vectorcall dMultiplyAddLeft(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span<float> sGradient, const Core::Span<float> sRight, Core::Span<float> sDestination) noexcept;

		static void __vectorcall dMultiplyRight(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span<float> sGradient, const Core::Span<float> sLeft, Core::Span<float> sDestination) noexcept;
		static void __vectorcall dMultiplyAddRight(std::size_t nMaxIndex, std::size_t nRow, std::size_t nColumn, const Core::Span<float> sGradient, const Core::Span<float> sLeft, Core::Span<float> sDestination) noexcept;
	};
}

#endif