
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_MSE_GPU_H

#define _CLASS_TINNET_LOSS_MSE_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../TinNet_GPU_Backend.h"

#include "cuda.h"

#include <cstddef>

namespace TinNet::Loss
{
	class TINNET_DLL MSE_GPU final
	{
	public:
		MSE_GPU() = delete;
		MSE_GPU(const MSE_GPU &sSrc) = delete;
		~MSE_GPU() = delete;
		
	public:
		MSE_GPU &operator=(const MSE_GPU &sSrc) = delete;
		
	public:
		static void derivative(std::size_t nBatchSize, std::size_t nOutputSize, CUdeviceptr pOutput, CUdeviceptr pDesiredOutput, CUdeviceptr pResult);
	};
}

#endif