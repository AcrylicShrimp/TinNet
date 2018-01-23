
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_CE_GPU_H

#define _CLASS_TINNET_LOSS_CE_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include "../TinNet_GPU_Backend.h"

#include "cuda.h"

#include <cstddef>

namespace TinNet::Loss
{
	class TINNET_DLL CE_GPU final
	{
	public:
		CE_GPU() = delete;
		CE_GPU(const CE_GPU &sSrc) = delete;
		~CE_GPU() = delete;
		
	public:
		CE_GPU &operator=(const CE_GPU &sSrc) = delete;
		
	public:
		static void derivative(std::size_t nBatchSize, std::size_t nOutputSize, CUdeviceptr pOutput, CUdeviceptr pDesiredOutput, CUdeviceptr pResult);
	};
}

#endif