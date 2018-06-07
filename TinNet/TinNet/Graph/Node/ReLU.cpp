
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "ReLU.h"

namespace TinNet::Graph::Node
{
	ReLU::ReLU(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &ReLU::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t ReLU::maxBackwardNodeCount() const
	{
		return 1;
	}

	void ReLU::initNode()
	{
		//Empty.
	}

	void ReLU::forwardPass(Cache sDestination)
	{
		const float vFactor[2]{.0f, 1.f};

		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = vFactor[.0f < sLeft[nIndex]] * sLeft[nIndex];
	}

	void ReLU::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const float vFactor[2]{.0f, 1.f};

		const auto &sForward{this->sBackwardList.front()->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = vFactor[.0f < sForward[nIndex]] * sBackward[nIndex];
	}
}