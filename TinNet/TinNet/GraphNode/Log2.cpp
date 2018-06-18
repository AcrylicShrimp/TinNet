
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Log2.h"

namespace TinNet::GraphNode
{
	Log2::Log2(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Log2::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Log2::type() const
	{
		return Log2::typeName();
	}

	void Log2::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::log2(sLeft[nIndex]);
	}

	void Log2::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] / (.6931472f * sLeft[nIndex]);
	}
}