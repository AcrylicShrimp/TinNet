
/*
	2019.04.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_COMPUTE_DENORMAL_H

#define _CLASS_TINNET_COMPUTE_DENORMAL_H

#include <immintrin.h>

namespace TinNet::Compute
{
	class Denormal final
	{
	public:
		const bool bFTZ;
		const bool bDAZ;
		
	public:
		Denormal();
		Denormal(const Denormal &sSrc) = delete;
		~Denormal();
		
	public:
		Denormal &operator=(const Denormal &sSrc) = delete;
	};
}

#endif