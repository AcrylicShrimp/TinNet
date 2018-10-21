
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Sin.h"

namespace TinNet::GraphNode
{
	Sin::Sin(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	Shape Sin::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Sin::type() const
	{
		return Sin::typeName();
	}

	void Sin::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::sin(sLeft[nIndex]);
	}

	void Sin::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * std::cos(sLeft[nIndex]);
	}
}