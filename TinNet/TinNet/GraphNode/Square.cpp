
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Square.h"

namespace TinNet::GraphNode
{
	Square::Square(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Square::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Square::type() const
	{
		return Square::typeName();
	}

	void Square::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = sLeft[nIndex] * sLeft[nIndex];
	}

	void Square::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * 2.f * sLeft[nIndex];
	}
}