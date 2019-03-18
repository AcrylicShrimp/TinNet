
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#include "SGD.h"

namespace TinNet::Optimizer
{
	SGD::SGD(std::initializer_list<Node::Parameter *> sParameterList) :
		sParameterList{sParameterList}
	{
		//Empty.
	}

	SGD::SGD(const std::vector<Node::Parameter *> &sParameterList) :
		sParameterList{sParameterList}
	{
		//Empty.
	}

	void SGD::reduce(float nLearningRate, Node::Node *pTarget)
	{
		for (auto *pParameter : this->sParameterList)
			pParameter->evalGradient(pTarget);

		for (auto *pParameter : this->sParameterList)
		{
			pParameter->parameter().accumulateFrom(-nLearningRate, pParameter->gradient());
			pParameter->markDirty();
		}
	}
}