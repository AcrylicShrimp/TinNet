
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Cos.h"

namespace TinNet::GraphNode
{
	Cos::Cos(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Cos::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Cos::type() const
	{
		return Cos::typeName();
	}

	void Cos::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::cos(sLeft[nIndex]);
	}

	void Cos::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] -= sGradient[nIndex] * std::sin(sLeft[nIndex]);
	}
}