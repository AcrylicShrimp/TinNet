
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "LogN.h"

namespace TinNet::GraphNode
{
	LogN::LogN(Graph *pGraph, const std::string &sName, float nBase) :
		FullNode(pGraph, sName),
		nLogBase{std::log(nBase)}
	{
		//Empty.
	}

	const Shape &LogN::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string LogN::type() const
	{
		return LogN::typeName();
	}

	void LogN::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::log(sLeft[nIndex] + .0001f) / this->nLogBase;
	}

	void LogN::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] / (this->nLogBase * sLeft[nIndex] + .0001f);
	}
}