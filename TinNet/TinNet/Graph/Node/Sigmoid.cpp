
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "Sigmoid.h"

namespace TinNet::Graph::Node
{
	Sigmoid::Sigmoid(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Sigmoid::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Sigmoid::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Sigmoid::initNode()
	{
		//Empty.
	}

	void Sigmoid::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = 1.f / (std::exp(-sLeft[nIndex]) + 1.f);
	}

	void Sigmoid::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sBackward[nIndex] * sForward[nIndex] * (1.f - sForward[nIndex]);
	}
}