
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Subtract.h"

namespace TinNet::GraphNode
{
	Subtract::Subtract(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Subtract::shape() const
	{
		return this->sShape;
	}

	std::string Subtract::type() const
	{
		return Subtract::typeName();
	}

	void Subtract::notifyShapeUpdated()
	{
		this->sShape = Shape::broadcast(this->sInputList.front()->shape(), this->sInputList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sInputList.front()->shape()}, Accessor{this->sInputList.back()->shape()});

		this->FullNode::notifyShapeUpdated();
	}

	void Subtract::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};
		auto sRight{this->sInputList.back()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sLeft[this->sIterator.index<1>()] - sRight[this->sIterator.index<2>()];
	}

	void Subtract::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};

		if (pInput == this->sInputList.front())
			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<1>()] += sGradient[this->sIterator.index<0>()];
		else
			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<2>()] -= sGradient[this->sIterator.index<0>()];
	}
}