
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#include "MulticlassCE_GPU.h"

namespace TinNet::Loss
{
	void MulticlassCE_GPU::derivative(std::size_t nBatchSize, std::size_t nOutputSize, CUdeviceptr pOutput, CUdeviceptr pDesiredOutput, CUdeviceptr pResult)
	{
		::MulticlassCE_GPU_derivative(nBatchSize, nOutputSize, pOutput, pDesiredOutput, pResult);
	}
}