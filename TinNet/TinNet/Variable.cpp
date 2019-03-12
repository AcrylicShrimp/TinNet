
/*
	2018.09.01
	Created by AcrylicShrimp.
*/

#include "Variable.h"

namespace TinNet
{
	Variable::Variable(Shape sShape, float *pBase, std::size_t nSize) :
		sShape{sShape},
		pBase{pBase},
		nSize{nSize}
	{
		//Empty.
	}
}