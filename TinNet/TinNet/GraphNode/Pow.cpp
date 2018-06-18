
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Pow.h"

namespace TinNet::GraphNode
{
	Pow::Pow(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Pow::shape() const
	{
		return this->sShape;
	}

	std::string Pow::type() const
	{
		return Pow::typeName();
	}

	void Pow::notifyShapeUpdated()
	{
		this->sShape = Shape::broadcast(this->sInputList.front()->shape(), this->sInputList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sInputList.front()->shape()}, Accessor{this->sInputList.back()->shape()});

		this->FullNode::notifyShapeUpdated();
	}

	void Pow::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};
		auto sRight{this->sInputList.back()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = std::pow(sLeft[this->sIterator.index<1>()], sRight[this->sIterator.index<2>()]);
	}

	void Pow::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		if (pInput == this->sInputList.front())
		{
			auto sRight{this->sInputList.back()->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<1>()] += sGradient[this->sIterator.index<0>()] * std::pow(sLeft[this->sIterator.index<1>()], sRight[this->sIterator.index<2>()] - 1.f) * sRight[this->sIterator.index<2>()];
		}
		else
		{
			auto sForward{this->forward()};

			for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
				sDestination[this->sIterator.index<2>()] += sGradient[this->sIterator.index<0>()] * sForward[this->sIterator.index<0>()] * std::log(sLeft[this->sIterator.index<1>()]);
		}
	}
}