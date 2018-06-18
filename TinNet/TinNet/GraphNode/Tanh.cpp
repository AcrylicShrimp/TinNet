
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Tanh.h"

namespace TinNet::GraphNode
{
	Tanh::Tanh(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Tanh::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Tanh::type() const
	{
		return Tanh::typeName();
	}

	void Tanh::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::tanh(sLeft[nIndex]);
	}

	void Tanh::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sForward{this->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * (1.f - sForward[nIndex] * sForward[nIndex]);
	}
}