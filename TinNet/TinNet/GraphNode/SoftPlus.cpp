
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Softplus.h"

namespace TinNet::GraphNode
{
	Softplus::Softplus(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	Shape Softplus::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Softplus::type() const
	{
		return Softplus::typeName();
	}

	void Softplus::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::log(std::exp(sLeft[nIndex]) + 1.f);
	}

	void Softplus::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * 1.f / (std::exp(-sLeft[nIndex]) + 1.f);
	}
}