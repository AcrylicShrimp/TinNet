
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
	
	Shape ReLU::shape() const
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

		std::size_t nIndex{0};
		std::size_t nMaxIndex{this->shape().element()};

		auto nAlpha{_mm256_set1_ps(this->nAlpha)};

		for (; nIndex + 8 <= nMaxIndex; nIndex += 8)
		{
			auto nLeft{_mm256_loadu_ps(&sLeft[nIndex])};
			_mm256_storeu_ps(&sDestination[nIndex], _mm256_max_ps(nLeft, _mm256_mul_ps(nLeft, nAlpha)));
		}

		float vTemp[2]{this->nAlpha, 1.f};

		for (; nIndex < nMaxIndex; ++nIndex)
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