
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "MSE_GPU.h"

namespace TinNet::Loss
{
	void MSE_GPU::derivative(std::size_t nBatchSize, std::size_t nOutputSize, CUdeviceptr pOutput, CUdeviceptr pDesiredOutput, CUdeviceptr pResult)
	{
		::MSE_GPU_derivative(nBatchSize, nOutputSize, pOutput, pDesiredOutput, pResult);
	}
}