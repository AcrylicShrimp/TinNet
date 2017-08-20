
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LOSS_MSE_H

#define _CLASS_CAYSNET_LOSS_MSE_H

#include <cstddef>

namespace CaysNet::Loss
{
	class MSE final
	{
	public:
		MSE() = delete;
		MSE(const MSE &sSrc) = delete;
		MSE(MSE &&sSrc) = delete;
		~MSE() = delete;
		
	public:
		MSE &operator=(const MSE &sSrc) = delete;
		MSE &operator=(MSE &&sSrc) = delete;
		
	public:
		static float loss(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput);
		static void derivative(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput, float *pResult);
	};
}

#endif