
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Input.h"

namespace TinNet::GraphNode
{
	Input::Input(Graph *pGraph, const std::string &sName, const Shape &sShape) :
		BackpropNode(pGraph, sName),
		Feedable(pGraph),
		sShapedCache{sShape}
	{
		//Empty.
	}

	const Shape &Input::shape() const
	{
		return this->sShapedCache.shape();
	}

	const std::string &Input::type() const
	{
		return "input";
	}

	Cache Input::forward()
	{
		return this->sShapedCache.cache();
	}

	void Input::feed(ShapedCache sShapedCache)
	{
		this->sShapedCache = sShapedCache;
	}

	void Input::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Input::backwardPass(Cache sDestination, NodePtr pInput)
	{
		sDestination.zero();
	}
}