
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_OPERAND2LOSSGRAPH_H

#define _CLASS_TINNET_LOSS_OPERAND2LOSSGRAPH_H

#include "Operand1LossGraph.h"

#define _TINNET_L_G_OP2_DEF const LossNode &pOperandLeft, const LossNode &pOperandRight
#define _TINNET_L_G_OP2_IMP Operand2LossGraph(pOperandLeft, pOperandRight)

namespace TinNet::Loss
{
	class Operand2LossGraph : public Operand1LossGraph
	{
	protected:
		LossNode pOperandRight;
		
	public:
		Operand2LossGraph(_TINNET_L_G_OP2_DEF);
		Operand2LossGraph(const Operand2LossGraph &sSrc) = default;
		~Operand2LossGraph() = default;
		
	public:
		Operand2LossGraph &operator=(const Operand2LossGraph &sSrc) = default;
		
	public:
		inline LossNode &operandRight();
		inline const LossNode &operandRight() const;
	};

	inline LossNode &Operand2LossGraph::operandRight()
	{
		return this->pOperandRight;
	}

	inline const LossNode &Operand2LossGraph::operandRight() const
	{
		return this->pOperandRight;
	}
}

#endif