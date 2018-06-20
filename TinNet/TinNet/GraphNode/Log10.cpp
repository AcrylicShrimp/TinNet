
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Log10.h"

namespace TinNet::GraphNode
{
	Log10::Log10(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	const Shape &Log10::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Log10::type() const
	{
		return Log10::typeName();
	}

	void Log10::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = std::log10(sLeft[nIndex] + .0001f);
	}

	void Log10::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] / (2.302585f * sLeft[nIndex]);
	}
}