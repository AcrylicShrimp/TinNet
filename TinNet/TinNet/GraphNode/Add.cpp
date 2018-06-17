
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Add.h"

namespace TinNet::GraphNode
{
	Add::Add(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Add::shape() const
	{
		return this->sShape;
	}

	const std::string &Add::type() const
	{
		return "add";
	}

	void Add::notifyShapeUpdated()
	{
		this->sShape = Shape::broadcast(this->sInputList.front()->shape(), this->sInputList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sInputList.front()->shape()}, Accessor{this->sInputList.back()->shape()});

		this->FullNode::notifyShapeUpdated();
	}

	void Add::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};
		auto sRight{this->sInputList.back()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sLeft[this->sIterator.index<1>()] + sRight[this->sIterator.index<2>()];
	}

	void Add::backwardPass(Cache sDestination, NodePtr pInput)
	{
		sDestination.zero();

		const auto &sGradient{this->backward()};

		if (pInput == this->sInputList.front())
			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<1>()] += sGradient[this->sIterator.index<0>()];
		else
			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<2>()] += sGradient[this->sIterator.index<0>()];
	}
}