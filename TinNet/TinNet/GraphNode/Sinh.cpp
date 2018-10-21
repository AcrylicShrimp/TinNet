
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Sinh.h"

namespace TinNet::GraphNode
{
	Sinh::Sinh(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	Shape Sinh::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Sinh::type() const
	{
		return Sinh::typeName();
	}

	void Sinh::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::sinh(sLeft[nIndex]);
	}

	void Sinh::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * std::cosh(sLeft[nIndex]);
	}
}