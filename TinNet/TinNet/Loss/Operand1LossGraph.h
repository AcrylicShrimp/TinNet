
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_OPERAND1LOSSGRAPH_H

#define _CLASS_TINNET_LOSS_OPERAND1LOSSGRAPH_H

#include "LossGraph.h"

#define _TINNET_L_G_OP1_DEF const LossNode &pOperandLeft
#define _TINNET_L_G_OP1_IMP Operand1LossGraph(pOperandLeft)

namespace TinNet::Loss
{
	class Operand1LossGraph : public LossGraph
	{
	protected:
		LossNode pOperandLeft;
		
	public:
		Operand1LossGraph(_TINNET_L_G_OP1_DEF);
		Operand1LossGraph(const Operand1LossGraph &sSrc) = default;
		~Operand1LossGraph() = default;
		
	public:
		Operand1LossGraph &operator=(const Operand1LossGraph &sSrc) = default;
		
	public:
		inline LossNode &operandLeft();
		inline const LossNode &operandLeft() const;
	};

	inline LossNode &Operand1LossGraph::operandLeft()
	{
		return this->pOperandLeft;
	}

	inline const LossNode &Operand1LossGraph::operandLeft() const
	{
		return this->pOperandLeft;
	}
}

#endif