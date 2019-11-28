
#ifndef _TINNET_COMPUTE_GEMM_H

#define _TINNET_COMPUTE_GEMM_H

#include "tinnet/includes/platform/CallingConvention.h"

#include <cstddef>

namespace tinnet::compute {
	class GEMM final {
	public:
		GEMM()	= delete;
		~GEMM() = delete;

	public:
		static void _TINNET_REGCALL multiply(
			std::size_t nMaxIndex,
			std::size_t nRow,
			std::size_t nColumn,
			const float *__restrict pL,
			const float *__restrict pR,
			float *__restrict pD) noexcept;
		static void _TINNET_REGCALL multiplyAdd(
			std::size_t nMaxIndex,
			std::size_t nRow,
			std::size_t nColumn,
			const float *__restrict pL,
			const float *__restrict pR,
			float *__restrict pD) noexcept;

		static void _TINNET_REGCALL dMultiplyLeft(
			std::size_t nMaxIndex,
			std::size_t nRow,
			std::size_t nColumn,
			const float *__restrict pG,
			const float *__restrict pR,
			float *__restrict pD) noexcept;
		static void _TINNET_REGCALL dMultiplyAddLeft(
			std::size_t nMaxIndex,
			std::size_t nRow,
			std::size_t nColumn,
			const float *__restrict pG,
			const float *__restrict pR,
			float *__restrict pD) noexcept;

		static void _TINNET_REGCALL dMultiplyRight(
			std::size_t nMaxIndex,
			std::size_t nRow,
			std::size_t nColumn,
			const float *__restrict pG,
			const float *__restrict pL,
			float *__restrict pD) noexcept;
		static void _TINNET_REGCALL dMultiplyAddRight(
			std::size_t nMaxIndex,
			std::size_t nRow,
			std::size_t nColumn,
			const float *__restrict pG,
			const float *__restrict pL,
			float *__restrict pD) noexcept;
	};
}	 // namespace tinnet::compute

#endif