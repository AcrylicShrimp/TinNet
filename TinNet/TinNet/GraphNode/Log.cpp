
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Log.h"

namespace TinNet::GraphNode
{
	Log::Log(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Log::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Log::type() const
	{
		return Log::typeName();
	}

	void Log::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::log(sLeft[nIndex]);
	}

	void Log::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{sDestination.size()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] / sLeft[nIndex];
	}
}