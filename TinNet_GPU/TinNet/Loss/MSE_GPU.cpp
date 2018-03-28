
/*
	2018.01.20
	Created by AcrylicShrimp.
*/

#include "MSE_GPU.h"

namespace TinNet::Loss
{
	void MSE_GPU::derivative(std::size_t nIndex, std::size_t nBatchSize, std::size_t nOutputSize, const GPUVector &sOutput, const GPUVector &sDesiredOutput, GPUVector &sResult)
	{
		::MSE_GPU_derivative(nIndex, nBatchSize, nOutputSize, sOutput, sDesiredOutput, sResult);
	}
}