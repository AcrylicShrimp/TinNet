
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Constant.h"

namespace TinNet::GraphNode
{
	Constant::Constant(Graph *pGraph, const std::string &sName, const Shape &sShape, const std::vector<float> &sValue) :
		BackpropNode(pGraph, sName),
		Feedable(pGraph),
		sShapedCache{sShape},
		sValue{sValue}
	{
		this->sShapedCache.set(this->sValue);
	}

	const Shape &Constant::shape() const
	{
		return this->sShapedCache.shape();
	}

	std::string Constant::type() const
	{
		return Constant::typeName();
	}

	Cache Constant::forward()
	{
		return this->sShapedCache.cache();
	}

	void Constant::feed(ShapedCache sShapedCache)
	{
		this->sShapedCache = sShapedCache;
	}

	void Constant::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Constant::backwardPass(Cache sDestination, NodePtr pConstant)
	{
		//Empty.
	}
}