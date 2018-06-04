
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "Tanh.h"

namespace TinNet::Graph::Node
{
	Tanh::Tanh(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Tanh::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Tanh::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Tanh::initNode()
	{
		this->sIterator.init(this->sBackwardList.front()->shape(), Accessor{this->sBackwardList.front()->shape()});
	}

	void Tanh::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = std::tanh(sLeft[this->sIterator.index<0>()]);
	}

	void Tanh::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sBackward{this->backward()};
		const auto &sForward{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sBackward[this->sIterator.index<0>()] * (1.f - sForward[this->sIterator.index<0>()] * sForward[this->sIterator.index<0>()]);
	}
}