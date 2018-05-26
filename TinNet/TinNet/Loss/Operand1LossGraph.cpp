
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "Operand1LossGraph.h"

namespace TinNet::Loss
{
	Operand1LossGraph::Operand1LossGraph(_TINNET_L_G_OP1_DEF) :
		pOperandLeft{pOperandLeft}
	{
		this->link(this->pOperandLeft.get());
	}
}