
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Add.h"

namespace TinNet::Graph::Node
{
	Add::Add(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph),
		sShape{}
	{
		//Empty.
	}

	const Shape &Add::shape() const
	{
		return this->sShape;
	}

	std::size_t Add::maxBackwardNodeCount() const
	{
		return 2;
	}

	void Add::initNode()
	{
		this->sShape = Shape::broadcast(this->sBackwardList.front()->shape(), this->sBackwardList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sBackwardList.front()->shape()}, Accessor{this->sBackwardList.back()->shape()});
	}

	void Add::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};
		const auto &sRight{this->sBackwardList.back()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sLeft[this->sIterator.index<1>()] + sRight[this->sIterator.index<2>()];
	}

	void Add::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.zero();

		const auto &sBackward{this->backward()};

		if (pBackward == this->sBackwardList.front())
			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<1>()] += sBackward[this->sIterator.index<0>()];
		else
			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<2>()] += sBackward[this->sIterator.index<0>()];
	}
}