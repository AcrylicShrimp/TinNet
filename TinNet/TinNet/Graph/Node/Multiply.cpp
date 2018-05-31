
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Multiply.h"

namespace TinNet::Graph::Node
{
	Multiply::Multiply(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph),
		sShape{}
	{
		//Empty.
	}

	const Shape &Multiply::shape() const
	{
		return this->sShape;
	}

	std::size_t Multiply::maxBackwardNodeCount() const
	{
		return 2;
	}

	void Multiply::initNode()
	{
		this->sShape = Shape::broadcast(this->sBackwardList.front()->shape(), this->sBackwardList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sBackwardList.front()->shape()}, Accessor{this->sBackwardList.back()->shape()});
	}

	void Multiply::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};
		const auto &sRight{this->sBackwardList.back()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sLeft[this->sIterator.index<1>()] * sRight[this->sIterator.index<2>()];
	}

	void Multiply::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.zero();

		const auto &sBackward{this->backward()};

		if (pBackward == this->sBackwardList.front())
		{
			const auto &sForward{this->sBackwardList.back()->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<1>()] = sBackward[this->sIterator.index<0>()] * sForward[this->sIterator.index<2>()];
		}
		else
		{
			const auto &sForward{this->sBackwardList.front()->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<2>()] = sBackward[this->sIterator.index<0>()] * sForward[this->sIterator.index<1>()];
		}
	}
}