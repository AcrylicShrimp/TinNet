
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Tan.h"

namespace TinNet::GraphNode
{
	Tan::Tan(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Tan::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Tan::type() const
	{
		return Tan::typeName();
	}

	void Tan::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::tan(sLeft[nIndex]);
	}

	void Tan::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sForward{this->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * (sForward[nIndex] * sForward[nIndex] + 1.f);
	}
}