
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Cosh.h"

namespace TinNet::GraphNode
{
	Cosh::Cosh(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Cosh::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Cosh::type() const
	{
		return Cosh::typeName();
	}

	void Cosh::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::cosh(sLeft[nIndex]);
	}

	void Cosh::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * std::sinh(sLeft[nIndex]);
	}
}