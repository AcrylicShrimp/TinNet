
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LOSS_ADDLOSSGRAPH_H

#define _CLASS_TINNET_LOSS_ADDLOSSGRAPH_H

#include "Operand2LossGraph.h"

namespace TinNet::Loss
{
	class AddLossGraph final : public Operand2LossGraph
	{
	public:
		AddLossGraph(_TINNET_L_G_OP2_DEF);
		AddLossGraph(const AddLossGraph &sSrc) = default;
		~AddLossGraph() = default;
		
	public:
		AddLossGraph &operator=(const AddLossGraph &sSrc) = default;
		
	public:
		virtual std::size_t fanOut() const override;
		virtual void forward(float *pResult) override;
		virtual void backwardPath(LossGraph *pBackward, float *pResult) override;
	};
}

#endif