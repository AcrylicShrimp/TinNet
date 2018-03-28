
/*
	2018.01.23
	Created by AcrylicShrimp.
*/

#include "CE_GPU.h"

namespace TinNet::Loss
{
	void CE_GPU::derivative(std::size_t nIndex, std::size_t nBatchSize, std::size_t nOutputSize, const GPUVector &sOutput, const GPUVector &sDesiredOutput, GPUVector &sResult)
	{
		::CE_GPU_derivative(nIndex, nBatchSize, nOutputSize, sOutput, sDesiredOutput, sResult);
	}
}