
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#include "LossGraph.h"

namespace TinNet::Loss
{
	LossGraph::LossGraph() :
		pForward{nullptr}
	{
		//Empty.
	}

	void LossGraph::backward(float *pResult)
	{
		if (this->pForward)
		{
			this->pForward->backwardPath(this, pResult);
			return;
		}

		std::fill(pResult, pResult + this->fanOut(), 1.f);
	}

	void LossGraph::link(LossGraph *pBackward)
	{
		pBackward->pForward = this;
	}
}