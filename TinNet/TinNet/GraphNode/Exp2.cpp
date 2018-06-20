
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Exp2.h"

namespace TinNet::GraphNode
{
	Exp2::Exp2(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}
	
	const Shape &Exp2::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Exp2::type() const
	{
		return Exp2::typeName();
	}

	void Exp2::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::exp2(sLeft[nIndex]);
	}

	void Exp2::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sForward{this->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * sForward[nIndex] * .6931472f;
	}
}