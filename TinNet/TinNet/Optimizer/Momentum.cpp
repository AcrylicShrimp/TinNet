
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#include "Momentum.h"

namespace TinNet::Optimizer
{
	Momentum::Momentum(Graph &sGraph, float nMomentum) :
		OptimizerBase(sGraph),
		nMomentum{nMomentum}
	{
		//Empty.
	}

	void Momentum::applyGradient(float nLearningRate)
	{
		for (auto &sGradient : this->sGradient)
			for (auto &sGradient : sGradient)
				for (auto &nGradient : sGradient)
					nGradient *= this->nMomentum;

		this->OptimizerBase::accumulateGradient(this->sGradient, nLearningRate);
		this->OptimizerBase::applyGradient(1.f, this->sGradient);
	}
}