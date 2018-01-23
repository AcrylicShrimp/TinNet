
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_CE_H

#define _CLASS_TINNET_LOSS_CE_H

#include "../TinNetDLL.h"

#include <cmath>

namespace TinNet::Loss
{
	class TINNET_DLL CE final
	{
	public:
		CE() = delete;
		CE(const CE &sSrc) = delete;
		CE(CE &&sSrc) = delete;
		~CE() = delete;
		
	public:
		CE &operator=(const CE &sSrc) = delete;
		CE &operator=(CE &&sSrc) = delete;
		
	public:
		static float loss(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput);
		static void derivative(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput, float *pResult);
	};
}

#endif