
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#include "Constant.h"

namespace TinNet::Initializer
{
	Constant::Constant(float nConstant) :
		nConstant{nConstant}
	{
		//Empty.
	}

	void Constant::operator()(Core::Span sSpan)
	{
		sSpan.fillScalar(this->nConstant);
	}
}