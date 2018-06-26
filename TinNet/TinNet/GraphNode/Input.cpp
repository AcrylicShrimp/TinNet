
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

	std::string Input::type() const
	{
		return Input::typeName();
	}

	Cache Input::forward()
	{
		return this->sShapedCache.cache();
	}

	void Input::feed(const Batch &sBatch, const ShapedCache &sShapedCache)
	{
		if (this->sValue.size() < sShapedCache.shape().element())
			this->sValue.resize(sShapedCache.shape().element());

		this->sShapedCache = sShapedCache.shape();
		this->sShapedCache.set(this->sValue);

		sBatch.copy(sShapedCache.shape().element() / sBatch.currentBatchSize(), sShapedCache.cache(), this->sValue);
	}

	void Input::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Input::backwardPass(Cache sDestination, NodePtr pInput)
	{
		//Empty.
	}
}