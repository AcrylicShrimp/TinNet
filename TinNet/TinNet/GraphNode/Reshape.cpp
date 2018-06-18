
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Reshape.h"

namespace TinNet::GraphNode
{
	Reshape::Reshape(Graph *pGraph, const std::string &sName, const Shape &sShape) :
		BackpropNode(pGraph, sName),
		sShape{sShape}
	{
		//Empty.
	}

	const Shape &Reshape::shape() const
	{
		return this->sShape;
	}

	std::string Reshape::type() const
	{
		return Reshape::typeName();
	}

	Cache Reshape::forward()
	{
		return this->sInputList.front()->forward();
	}

	void Reshape::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Reshape::backwardPass(Cache sDestination, NodePtr pInput)
	{
		sDestination.accumulate(this->backward());
	}
}