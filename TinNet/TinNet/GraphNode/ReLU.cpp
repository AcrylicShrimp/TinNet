
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "ReLU.h"

namespace TinNet::GraphNode
{
	ReLU::ReLU(Graph *pGraph, const std::string &sName, float nAlpha) :
		FullNode(pGraph, sName),
		nAlpha{nAlpha}
	{
		//Empty.
	}
	
	const Shape &ReLU::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string ReLU::type() const
	{
		return ReLU::typeName();
	}

	void ReLU::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		float vTemp[2]{this->nAlpha, 1.f};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] = sLeft[nIndex] * vTemp[sLeft[nIndex] > .0f];
	}

	void ReLU::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		float vTemp[2]{this->nAlpha, 1.f};

		for (std::size_t nIndex{0}, nMaxIndex{this->shape().element()}; nIndex < nMaxIndex; ++nIndex)
			sDestination[nIndex] += sGradient[nIndex] * vTemp[sLeft[nIndex] > .0f];
	}
}