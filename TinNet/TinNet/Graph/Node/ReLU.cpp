
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "ReLU.h"

namespace TinNet::Graph::Node
{
	ReLU::ReLU(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &ReLU::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t ReLU::maxBackwardNodeCount() const
	{
		return 1;
	}

	void ReLU::initNode()
	{
		this->sIterator.init(this->sBackwardList.front()->shape(), Accessor{this->sBackwardList.front()->shape()});
	}

	void ReLU::forwardPass(Cache sDestination)
	{
		const float vFactor[2]{.0f, 1.f};

		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = vFactor[.0f < sLeft[this->sIterator.index<0>()]] * sLeft[this->sIterator.index<0>()];
	}

	void ReLU::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const float vFactor[2]{.0f, 1.f};

		const auto &sBackward{this->backward()};
		const auto &sForward{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = vFactor[.0f < sForward[this->sIterator.index<0>()]] * sBackward[this->sIterator.index<0>()];
	}
}