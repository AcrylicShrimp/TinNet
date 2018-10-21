
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Squeeze.h"

namespace TinNet::GraphNode
{
	Squeeze::Squeeze(Graph *pGraph, const std::string &sName) :
		BackpropNode(pGraph, sName),
		sShape{}
	{
		//Empty.
	}

	Shape Squeeze::shape() const
	{
		return this->sShape;
	}

	std::string Squeeze::type() const
	{
		return Squeeze::typeName();
	}

	void Squeeze::notifyShapeUpdated()
	{
		this->sShape = this->sInputList.front()->shape().squeeze();

		this->BackpropNode::notifyShapeUpdated();
	}

	Cache Squeeze::forward()
	{
		return this->sInputList.front()->forward();
	}

	void Squeeze::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Squeeze::backwardPass(Cache sDestination, NodePtr pInput)
	{
		sDestination.accumulate(this->backward());
	}
}