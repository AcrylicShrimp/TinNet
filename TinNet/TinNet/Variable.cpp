
/*
	2018.09.01
	Created by AcrylicShrimp.
*/

#include "Variable.h"

namespace TinNet
{
	Variable::Variable(Shape sShape, float *pBegin, std::size_t nSize) :
		sShape{sShape},
		pBegin{pBegin},
		nSize{nSize}
	{
		//Empty.
	}
}