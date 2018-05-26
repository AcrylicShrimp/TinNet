
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "Operand2LossGraph.h"

namespace TinNet::Loss
{
	Operand2LossGraph::Operand2LossGraph(_TINNET_L_G_OP2_DEF) :
		_TINNET_L_G_OP1_IMP,
		pOperandRight{pOperandRight}
	{
		this->link(this->pOperandRight.get());
	}
}