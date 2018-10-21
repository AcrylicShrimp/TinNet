
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "Sign.h"

namespace TinNet::GraphNode
{
	Sign::Sign(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName)
	{
		//Empty.
	}

	Shape Sign::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Sign::type() const
	{
		return Sign::typeName();
	}

	void Sign::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = (.0f < sLeft[nIndex]) - (.0f > sLeft[nIndex]);
	}

	void Sign::backwardPass(Cache sDestination, NodePtr pInput)
	{
		//Empty.
	}
}