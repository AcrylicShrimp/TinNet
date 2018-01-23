
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#include "CE_GPU.h"

namespace TinNet::Loss
{
	void CE_GPU::derivative(std::size_t nBatchSize, std::size_t nOutputSize, CUdeviceptr pOutput, CUdeviceptr pDesiredOutput, CUdeviceptr pResult)
	{
		::CE_GPU_derivative(nBatchSize, nOutputSize, pOutput, pDesiredOutput, pResult);
	}
}