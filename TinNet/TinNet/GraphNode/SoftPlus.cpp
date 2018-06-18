
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "SoftPlus.h"

namespace TinNet::GraphNode
{
	SoftPlus::SoftPlus(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &SoftPlus::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string SoftPlus::type() const
	{
		return SoftPlus::typeName();
	}

	void SoftPlus::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::log(std::exp(sLeft[nIndex]) + 1.f);
	}

	void SoftPlus::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * 1.f / (std::exp(-sLeft[nIndex]) + 1.f);
	}
}