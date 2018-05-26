
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "AddLossGraph.h"

namespace TinNet::Loss
{
	AddLossGraph::AddLossGraph(_TINNET_L_G_OP2_DEF) :
		_TINNET_L_G_OP2_IMP
	{
		//Empty.
	}

	std::size_t AddLossGraph::fanOut() const
	{
		return this->pOperandLeft->fanOut();
	}

	void AddLossGraph::forward(float *pResult)
	{

	}

	void AddLossGraph::backwardPath(LossGraph *pBackward, float *pResult)
	{

	}
}