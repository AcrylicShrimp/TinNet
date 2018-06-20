
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Exp.h"

namespace TinNet::GraphNode
{
	Exp::Exp(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}
	
	const Shape &Exp::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Exp::type() const
	{
		return Exp::typeName();
	}

	void Exp::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::exp(sLeft[nIndex]);
	}

	void Exp::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sForward{this->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * sForward[nIndex];
	}
}