
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "Sigmoid.h"

namespace TinNet::Graph::Node
{
	Sigmoid::Sigmoid(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Sigmoid::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Sigmoid::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Sigmoid::initNode()
	{
		this->sIterator.init(this->sBackwardList.front()->shape(), Accessor{this->sBackwardList.front()->shape()});
	}

	void Sigmoid::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = 1.f / (std::exp(-sLeft[this->sIterator.index<0>()]) + 1.f);
	}

	void Sigmoid::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sBackward{this->backward()};
		const auto &sForward{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sBackward[this->sIterator.index<0>()] * sForward[this->sIterator.index<0>()] * (1.f - sForward[this->sIterator.index<0>()]);
	}
}