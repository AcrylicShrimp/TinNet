
/*
	2018.06.27
	Created by AcrylicShrimp.
*/

#include "Select.h"

namespace TinNet::GraphNode
{
	Select::Select(Graph *pGraph, const std::string &sName) :
		BackpropNode(pGraph, sName),
		Feedable(pGraph, this)
	{
		//Empty.
	}

	Shape Select::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Select::type() const
	{
		return Select::typeName();
	}

	Cache Select::forward()
	{
		if (this->bCondition)
			return this->sInputList.front()->forward();
		else
			return this->sInputList.back()->forward();
	}

	void Select::feed(const ShapedCache &sShapedCache)
	{
		this->bCondition = sShapedCache.cache()[0] < .5f;
	}

	void Select::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Select::backwardPass(Cache sDestination, NodePtr pInput)
	{
		if (this->bCondition == (pInput == this->sInputList.front()))
			sDestination.accumulate(this->backward());
	}
}