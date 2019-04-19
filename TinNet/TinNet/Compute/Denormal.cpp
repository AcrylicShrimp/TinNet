
/*
	2019.04.19
	Created by AcrylicShrimp.
*/

#include "Denormal.h"

namespace TinNet::Compute
{
	Denormal::Denormal() :
		bFTZ{_MM_GET_FLUSH_ZERO_MODE() == _MM_FLUSH_ZERO_ON},
		bDAZ{_MM_GET_DENORMALS_ZERO_MODE() == _MM_DENORMALS_ZERO_ON}
	{
		_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
		_MM_GET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
	}
	
	Denormal::~Denormal()
	{
		_MM_SET_FLUSH_ZERO_MODE(this->bFTZ ? _MM_FLUSH_ZERO_ON : _MM_FLUSH_ZERO_OFF);
		_MM_GET_DENORMALS_ZERO_MODE(this->bDAZ ? _MM_DENORMALS_ZERO_ON : _MM_DENORMALS_ZERO_OFF);
	}
}