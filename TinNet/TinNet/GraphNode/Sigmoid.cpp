
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Sigmoid.h"

namespace TinNet::GraphNode
{
	Sigmoid::Sigmoid(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Sigmoid::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Sigmoid::type() const
	{
		return Sigmoid::typeName();
	}

	void Sigmoid::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = 1.f / (std::exp(-sLeft[nIndex]) + 1.f);
	}

	void Sigmoid::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sForward{this->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * sForward[nIndex] * (1.f - sForward[nIndex]);
	}
}