
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_MULTICLASS_CE_H

#define _CLASS_TINNET_LOSS_MULTICLASS_CE_H

#include "../TinNetDLL.h"

#include <cmath>

namespace TinNet::Loss
{
	class TINNET_DLL MulticlassCE
	{
	public:
		MulticlassCE() = delete;
		MulticlassCE(const MulticlassCE &sSrc) = delete;
		MulticlassCE(MulticlassCE &&sSrc) = delete;
		~MulticlassCE() = delete;

	public:
		MulticlassCE &operator=(const MulticlassCE &sSrc) = delete;
		MulticlassCE &operator=(MulticlassCE &&sSrc) = delete;
		
	public:
		static float loss(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput);
		static void derivative(std::size_t nLength, const float *pNetworkOutput, const float *pDesiredOutput, float *pResult);
	};
}

#endif