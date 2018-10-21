
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Multiply.h"

namespace TinNet::GraphNode
{
	Multiply::Multiply(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}
	
	Shape Multiply::shape() const
	{
		return this->sShape;
	}

	std::string Multiply::type() const
	{
		return Multiply::typeName();
	}

	void Multiply::notifyShapeUpdated()
	{
		this->sShape = Shape::broadcast(this->sInputList.front()->shape(), this->sInputList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sInputList.front()->shape()}, Accessor{this->sInputList.back()->shape()});

		this->FullNode::notifyShapeUpdated();
	}

	void Multiply::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};
		auto sRight{this->sInputList.back()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sLeft[this->sIterator.index<1>()] * sRight[this->sIterator.index<2>()];
	}

	void Multiply::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};

		if (pInput == this->sInputList.front())
		{
			auto sRight{this->sInputList.back()->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<1>()] += sGradient[this->sIterator.index<0>()] * sRight[this->sIterator.index<2>()];
		}
		else
		{
			auto sLeft{this->sInputList.front()->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<2>()] += sGradient[this->sIterator.index<0>()] * sLeft[this->sIterator.index<1>()];
		}
	}
}