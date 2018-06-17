
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Divide.h"

namespace TinNet::GraphNode
{
	Divide::Divide(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}
	
	const Shape &Divide::shape() const
	{
		return this->sShape;
	}

	std::string Divide::type() const
	{
		return Divide::typeName();
	}

	void Divide::notifyShapeUpdated()
	{
		this->sShape = Shape::broadcast(this->sInputList.front()->shape(), this->sInputList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sInputList.front()->shape()}, Accessor{this->sInputList.back()->shape()});

		this->FullNode::notifyShapeUpdated();
	}

	void Divide::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};
		auto sRight{this->sInputList.back()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = sLeft[this->sIterator.index<1>()] / (sRight[this->sIterator.index<2>()] + .0001f);
	}

	void Divide::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};

		if (pInput == this->sInputList.front())
		{
			auto sForward{this->sInputList.back()->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<1>()] += sGradient[this->sIterator.index<0>()] / (sForward[this->sIterator.index<2>()] + .0001f);
		}
		else
		{
			auto sForwardLeft{this->sInputList.front()->forward()};
			auto sForwardRight{this->sInputList.back()->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<2>()] -= sGradient[this->sIterator.index<0>()] * sForwardLeft[this->sIterator.index<1>()] / (sForwardRight[this->sIterator.index<2>()] * sForwardRight[this->sIterator.index<2>()] + .0001f);
		}
	}
}