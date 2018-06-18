
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Abs.h"

namespace TinNet::GraphNode
{
	Abs::Abs(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Abs::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Abs::type() const
	{
		return Abs::typeName();
	}

	void Abs::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::abs(sLeft[nIndex]);
	}

	void Abs::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sForward{this->forward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * sForward[nIndex] / sLeft[nIndex];
	}
}