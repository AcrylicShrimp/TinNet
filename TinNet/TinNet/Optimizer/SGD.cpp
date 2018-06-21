
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#include "SGD.h"

namespace TinNet::Optimizer
{
	SGD::SGD(Graph &sGraph) :
		OptimizerBase(sGraph)
	{
		//Empty.
	}

	void SGD::applyGradient(float nLearningRate)
	{
		this->OptimizerBase::copyGradient(this->sGradient);
		this->OptimizerBase::applyGradient(nLearningRate, this->sGradient);
	}
}