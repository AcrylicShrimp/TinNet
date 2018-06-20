
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Neg.h"

namespace TinNet::GraphNode
{
	Neg::Neg(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}
	
	const Shape &Neg::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Neg::type() const
	{
		return Neg::typeName();
	}

	void Neg::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = -sLeft[nIndex];
	}

	void Neg::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] -= sGradient[nIndex];
	}
}