
/*
	2019.08.16
	Created by AcrylicShrimp.
*/

#include "Momentum.h"

namespace TinNet::Optimizer
{
	Momentum::Momentum(float nMomentum, std::initializer_list<Node::Parameter *> sParameterList) :
		nMomentum{nMomentum},
		sParameterList{sParameterList}
	{
		for (auto *pParameter : this->sParameterList)
			this->sMomentumGradientList.emplace_back(pParameter->evalShape().shape().size());

		for (auto &sMomentumGradient : this->sMomentumGradientList)
			sMomentumGradient.span().fillZero();
	}

	Momentum::Momentum(float nMomentum, const std::vector<Node::Parameter *> &sParameterList) :
		nMomentum{nMomentum},
		sParameterList{sParameterList}
	{
		for (auto *pParameter : this->sParameterList)
			this->sMomentumGradientList.emplace_back(pParameter->evalShape().shape().size());

		for (auto &sMomentumGradient : this->sMomentumGradientList)
			sMomentumGradient.span().fillZero();
	}
	
	void Momentum::reduce(float nLearningRate, Node::Node *pTarget)
	{
		for (auto *pParameter : this->sParameterList)
			pParameter->evalGradient(pTarget);

		auto iMomentumGradient{this->sMomentumGradientList.begin()};

		for (auto *pParameter : this->sParameterList)
		{
			for (auto &nGradient : iMomentumGradient->span())
				nGradient *= this->nMomentum;

			iMomentumGradient->span().accumulateFrom(pParameter->gradient());
			pParameter->parameter().accumulateFrom(-nLearningRate, iMomentumGradient->span());
			pParameter->markDirty(false);

			++iMomentumGradient;
		}
	}
}